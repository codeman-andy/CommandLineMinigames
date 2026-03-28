#include "AI.h"

AI::AI(const char* name) {
	m_name = name;
	m_valid_moves = nullptr;
	m_nr_of_valid_moves = 1;
}

size_t AI::FindMoveIndex(move move) const {
	size_t index = 0;
	while (m_valid_moves[index] != move) index++;
	return index;
}

void AI::DecrementValidMoves(size_t index) {
	for (index; index < m_nr_of_valid_moves; index++) m_valid_moves[index] = m_valid_moves[index + 1];
}

void AI::SetValidMoves(size_t dimensions_lengths[]) {
	for (size_t i = 0; i < 2; i++) {
		m_nr_of_valid_moves = m_nr_of_valid_moves * dimensions_lengths[i];
	}

	m_valid_moves = new move[m_nr_of_valid_moves];

	size_t idx = 0;
	for (size_t i = 0; i < dimensions_lengths[0]; i++) {
		for (size_t j = 0; j < dimensions_lengths[1]; j++) {
			m_valid_moves[idx].y = i;
			m_valid_moves[idx].x = j;
			idx++;
		}
	}
}

void AI::RemoveFromValidMoves(move move) {
	m_nr_of_valid_moves--;

	size_t index = FindMoveIndex(move);

	DecrementValidMoves(index);
}

move AI::MakeRandomMove() const {
	size_t random_index = rand() % (m_nr_of_valid_moves - 1);
	return m_valid_moves[random_index];
}

int AI::FindWinningMoveInRows(move& winning_move, size_t board[3][3], size_t row_count[3], size_t my_letter) {
	size_t my_letter_count;
	move available_spot = move();

	for (size_t row = 0; row < 3; row++) {
		if (row_count[row] < 2) continue;

		my_letter_count = 0;
		size_t col = 0;
		for (col; col < 3; col++) {
			if (board[row][col] == my_letter) my_letter_count++;
			else if (board[row][col] == UNOCCUPIED) available_spot = move(col, row);
		}

		if (my_letter_count == 2) {
			winning_move = available_spot;
			return WINNER_FOUND;
		}
	}

	return RUNNING;
}

int AI::FindWinningMoveInCols(move& winning_move, size_t board[3][3], size_t col_count[3], size_t my_letter) {
	size_t my_letter_count;
	move available_spot = move();

	for (size_t col = 0; col < 3; col++) {
		if (col_count[col] < 2) continue;

		my_letter_count = 0;
		size_t row = 0;
		for (row; row < 3; row++) {
			if (board[row][col] == my_letter) my_letter_count++;
			else if (board[row][col] == UNOCCUPIED) available_spot = move(col, row);
		}

		if (my_letter_count == 2) {
			winning_move = available_spot;
			return WINNER_FOUND;
		}
	}

	return RUNNING;
}

int AI::FindWinningMoveInDiagonals(move& winning_move, size_t board[3][3], size_t diagonal_count[2], size_t my_letter) {
	size_t my_letter_count;
	move available_spot = move();

	if (diagonal_count[0] == 2) {
		my_letter_count = 0;
		size_t equal = 0;
		for (equal; equal < 3; equal++) {
			if (board[equal][equal] == my_letter) my_letter_count++;
			else if (board[equal][equal] == UNOCCUPIED) available_spot = move(equal, equal);
		}

		if (my_letter_count == 2) {
			winning_move = available_spot;
			return WINNER_FOUND;
		}
	}

	if (diagonal_count[1] == 2) {
		my_letter_count = 0;

		size_t alternate = 0;
		for (alternate; alternate < 3; alternate++) {
			if (board[alternate][2 - alternate] == my_letter) my_letter_count++;
			else if (board[alternate][2 - alternate] == UNOCCUPIED) available_spot = move(2 - alternate, alternate);
		}

		if (my_letter_count == 2) {
			winning_move = available_spot;
			return WINNER_FOUND;
		}
	}

	return RUNNING;
}

int AI::FindWinningMove(move& winning_move, size_t board[3][3], size_t row_count[3], size_t col_count[3], size_t diagonal_count[2]) {
	size_t my_letter = TicTacToe::GetCurrentLetter();

	if (FindWinningMoveInRows(winning_move, board, row_count, my_letter) == WINNER_FOUND) return WINNER_FOUND;

	if (FindWinningMoveInCols(winning_move, board, col_count, my_letter) == WINNER_FOUND) return WINNER_FOUND;

	if (FindWinningMoveInDiagonals(winning_move, board, diagonal_count, my_letter) == WINNER_FOUND) return WINNER_FOUND;

	return RUNNING;
}

move AI::FindWinOrMakeRandomMove(size_t board[3][3], size_t row_count[3], size_t col_count[3], size_t diagonal_count[2]) const {
	move winning_move(-33, -33);

	if (FindWinningMove(winning_move, board, row_count, col_count, diagonal_count) == WINNER_FOUND) return winning_move;

	else return MakeRandomMove();
}

AI* AI::CreatePlayer(const char* name) {

	AI* ptr = new AI(name);

	return ptr;
}

/* VERY PRIMITIVE, PROOF OF CONCEPT ATTEMPT AT AI
move AI::DecideMove(size_t board[3][3], size_t rows[3], size_t cols[3], size_t diagonals[2], letter my_letter) {
	move decision = move();
	size_t win_c = 0;
	for (size_t i = 0; (i < 3 && rows[i] < FULL); i++) {
		if (my_letter * rows[i] == board[i][0] + board[i][1] + board[i][2]) {
			if (my_letter * rows[i] > win_c) {
				size_t k = 0;
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
				size_t m = 0;
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