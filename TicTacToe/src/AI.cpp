#include "AI.h"

AI::AI(const char* name) {
	m_name = name;
	m_valid_moves = nullptr;
	m_nr_of_valid_moves = 1;
}

int AI::FindMoveIndex(move move) const {
	int index = 0;
	while (m_valid_moves[index] != move) index++;
	return index;
}

void AI::DecrementValidMoves(int index) {
	for (index; index < m_nr_of_valid_moves; index++) m_valid_moves[index] = m_valid_moves[index + 1];
}

/**
void AI::CopyBoard(int board[3][3], int new_board[3][3]) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			new_board[col][row] = board[col][row];
		}
	}
}
*/

void AI::SetValidMoves(move* valid_moves) {
	m_valid_moves = valid_moves;
}

/*
void AI::SetValidMoves(int dimensions_lengths[]) {
	for (int i = 0; i < 2; i++) {
		m_nr_of_valid_moves = m_nr_of_valid_moves * dimensions_lengths[i];
	}

	m_valid_moves = new move[m_nr_of_valid_moves];

	int idx = 0;
	for (int i = 0; i < dimensions_lengths[0]; i++) {
		for (int j = 0; j < dimensions_lengths[1]; j++) {
			m_valid_moves[idx].y = i;
			m_valid_moves[idx].x = j;
			idx++;
		}
	}
}
*/

void AI::RemoveFromValidMoves(move move) {
	m_nr_of_valid_moves--;

	int index = FindMoveIndex(move);

	DecrementValidMoves(index);
}

move AI::MakeRandomMove() const {
	int random_index = rand() % (m_nr_of_valid_moves - 1);
	return m_valid_moves[random_index];
}

int AI::FindWinningMoveInRows(move& winning_move, ttt_board board, int my_letter) {
	int my_letter_count;
	move available_spot = move();

	for (int row = 0; row < 3; row++) {
		if (board.row_counter[row] != 2) continue;

		my_letter_count = 0;
		int col = 0;
		for (col; col < 3; col++) {
			if (board.coordinates[row][col] == my_letter) my_letter_count++;
			else if (board.coordinates[row][col] == UNOCCUPIED) available_spot = move(col, row);
		}

		if (my_letter_count == 2) {
			winning_move = available_spot;
			return WINNER_FOUND;
		}
	}

	return RUNNING;
}

int AI::FindWinningMoveInCols(move& winning_move, ttt_board board, int my_letter) {
	int my_letter_count;
	move available_spot = move();

	for (int col = 0; col < 3; col++) {
		if (board.col_counter[col] != 2) continue;

		my_letter_count = 0;
		int row = 0;
		for (row; row < 3; row++) {
			if (board.coordinates[row][col] == my_letter) my_letter_count++;
			else if (board.coordinates[row][col] == UNOCCUPIED) available_spot = move(col, row);
		}

		if (my_letter_count == 2) {
			winning_move = available_spot;
			return WINNER_FOUND;
		}
	}

	return RUNNING;
}

int AI::FindWinningMoveInDiagonals(move& winning_move, ttt_board board, int my_letter) {
	int my_letter_count;
	move available_spot = move();

	if (board.diagonal_counter[0] == 2) {
		my_letter_count = 0;
		int equal = 0;
		for (equal; equal < 3; equal++) {
			if (board.coordinates[equal][equal] == my_letter) my_letter_count++;
			else if (board.coordinates[equal][equal] == UNOCCUPIED) available_spot = move(equal, equal);
		}

		if (my_letter_count == 2) {
			winning_move = available_spot;
			return WINNER_FOUND;
		}
	}

	if (board.diagonal_counter[1] == 2) {
		my_letter_count = 0;

		int alternate = 0;
		for (alternate; alternate < 3; alternate++) {
			if (board.coordinates[alternate][2 - alternate] == my_letter) my_letter_count++;
			else if (board.coordinates[alternate][2 - alternate] == UNOCCUPIED) available_spot = move(2 - alternate, alternate);
		}

		if (my_letter_count == 2) {
			winning_move = available_spot;
			return WINNER_FOUND;
		}
	}

	return RUNNING;
}

int AI::FindWinningMove(move& winning_move, ttt_board board, int my_letter) {

	if (FindWinningMoveInRows(winning_move, board, my_letter) == WINNER_FOUND) return WINNER_FOUND;

	if (FindWinningMoveInCols(winning_move, board, my_letter) == WINNER_FOUND) return WINNER_FOUND;

	if (FindWinningMoveInDiagonals(winning_move, board, my_letter) == WINNER_FOUND) return WINNER_FOUND;

	return RUNNING;
}

move AI::FindWinOrMakeRandomMove(ttt_board board) const {
	int my_letter = TicTacToe::GetCurrentLetter();

	move winning_move(-33, -33);

	if (FindWinningMove(winning_move, board, my_letter) == WINNER_FOUND) return winning_move;

	else return MakeRandomMove();
}


move AI::FindWinOrPreventLossOrMakeRandomMove(ttt_board board) const {
	int my_letter = TicTacToe::GetCurrentLetter();

	move winning_move(-33, -33);

	if (FindWinningMove(winning_move, board, my_letter) == WINNER_FOUND) return winning_move;

	int opponent_letter = (my_letter == O) ? X : O;

	if (FindWinningMove(winning_move, board, opponent_letter) == WINNER_FOUND) return winning_move;

	else return MakeRandomMove();
}

int Min(int* scores, int length) {
	int min_value = 10;

	for (int i = 0; i < length; i++) {
		if (scores[i] < min_value) min_value = scores[i];
	}

	return min_value;
}

int Max(int* scores, int length) {
	int max_value = -10;

	for (int i = 0; i < length; i++) {
		if (scores[i] > max_value) max_value = scores[i];
	}

	return max_value;
}

int AI::MinMaxScore(move& last_move, ttt_board board, int last_letter) {

	int my_letter = TicTacToe::GetCurrentLetter();

	if (TicTacToe::CheckBoard(board, last_move.x, last_move.y) == WINNER_FOUND) {
		if (last_letter == my_letter) return 10;
		else return -10;
	}

	if (TicTacToe::CheckForDraw() == DRAW) return 0;

	move* valid_moves = TicTacToe::GetValidMoves(board);

	int* scores = new int[board.nr_of_available_moves];

	for (int move_index = 0; move_index < board.nr_of_available_moves; move_index++) {
		ttt_board new_board;
		new_board.CopyBoard(board);

		int next_letter = (last_letter == O) ? X : O;

		TicTacToe::MarkOnBoard(new_board, valid_moves[move_index].x, valid_moves[move_index].y, next_letter);

		int score = MinMaxScore(valid_moves[move_index], new_board, next_letter);

		scores[move_index] = score;
	}

	int r_score;

	if (last_letter == my_letter) r_score = Max(scores, board.nr_of_available_moves);

	else r_score = Min(scores, board.nr_of_available_moves);

	delete[](scores);

	return r_score;
}

int MinMaxMove(ttt_board board, int my_letter) {

}

AI* AI::CreatePlayer(const char* name) {

	AI* ptr = new AI(name);

	return ptr;
}

/* VERY PRIMITIVE, PROOF OF CONCEPT ATTEMPT AT AI
move AI::DecideMove(int board[3][3], int rows[3], int cols[3], int diagonals[2], letter my_letter) {
	move decision = move();
	int win_c = 0;
	for (int i = 0; (i < 3 && rows[i] < FULL); i++) {
		if (my_letter * rows[i] == board[i][0] + board[i][1] + board[i][2]) {
			if (my_letter * rows[i] > win_c) {
				int k = 0;
				while (board[i][k] != UNOCCUPIED) k++;
				decision.x = k;
				decision.y = i;
				win_c = my_letter * rows[i];
			}
		}
	}
	for (int j = 0; (j < 3 && cols[j] < FULL); j++) {
		if (my_letter * cols[j] == board[0][j] + board[1][j] + board[2][j]) {
			if (my_letter * cols[j] > win_c) {
				int m = 0;
				while (board[m][j] != UNOCCUPIED) m++;
				decision.x = j;
				decision.y = m;
				win_c = my_letter * cols[j];
			}
		}
	}
	std::cout << "Pam decided: [" << decision.y << ", " << decision.x << "]" << std::endl;
	return decision;
}
*/