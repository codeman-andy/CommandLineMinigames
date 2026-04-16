#include "AI.h"

#include "BoardTicTacToe.cpp"

AI::AI(const char* const& name, const difficulty& difficulty)
{
	m_name = name;
	m_valid_moves = nullptr;
	m_nr_of_valid_moves = 1;
	m_difficulty = difficulty;

	Difficulty = (m_difficulty == EASY) ? &AI::FindWinOrMakeRandomMove
		: (m_difficulty == MEDIUM) ? &AI::FindWinOrPreventLossOrMakeRandomMove
		: &AI::MinMaxMove;
}

void AI::SetDifficulty(const difficulty& difficulty)
{
	m_difficulty = difficulty;
}

int AI::FindMoveIndex(const move& move) const
{
	int index = 0;
	while (m_valid_moves[index] != move)
	{
		Log("Lul");
		index++;
	}
	return index;
}

void AI::DecrementValidMoves(int index)
{
	m_nr_of_valid_moves--;

	for (index; index < m_nr_of_valid_moves; index++) m_valid_moves[index] = m_valid_moves[index + 1];
}

void AI::SetValidMoves(move* const& valid_moves, const int& nr_of_valid_moves)
{
	m_valid_moves = valid_moves;
	m_nr_of_valid_moves = nr_of_valid_moves;
}

void AI::RemoveFromValidMoves(const move& move)
{
	int index = FindMoveIndex(move);

	DecrementValidMoves(index);
}

move& AI::MakeRandomMove() const
{
	int random_index = rand() % (m_nr_of_valid_moves - 1);
	return m_valid_moves[random_index];
}

int AI::FindWinningMoveInRows(move& winning_move, const TicTacToe::Board& board, const letter& my_letter)
{
	int my_letter_count;
	move available_move = move();

	for (int row = 0; row < 3; row++)
	{
		if (board.row_counter[row] != 2) continue;

		my_letter_count = 0;
		for (int col = 0; col < 3; col++)
		{
			if (board.coordinates[col][row] == my_letter) my_letter_count++;
			else if (board.coordinates[col][row] == UNOCCUPIED) available_move = move(col, row);
		}

		if (my_letter_count == 2)
		{
			winning_move = available_move;
			return WINNER_FOUND;
		}
	}

	return NOT_FOUND;
}

int AI::FindWinningMoveInCols(move& winning_move, const TicTacToe::Board& board, const letter& my_letter)
{
	int my_letter_count;
	move available_move = move();

	for (int col = 0; col < 3; col++)
	{
		if (board.col_counter[col] != 2) continue;

		my_letter_count = 0;
		for (int row = 0; row < 3; row++)
		{
			if (board.coordinates[col][row] == my_letter) my_letter_count++;
			else if (board.coordinates[col][row] == UNOCCUPIED) available_move = move(col, row);
		}

		if (my_letter_count == 2)
		{
			winning_move = available_move;
			return WINNER_FOUND;
		}
	}

	return NOT_FOUND;
}

int AI::FindWinningMoveInDiagonals(move& winning_move, const TicTacToe::Board& board, const letter& my_letter)
{
	int my_letter_count;
	move available_move = move();

	if (board.diagonal_counter[0] == 2)
	{
		my_letter_count = 0;
		for (int equal = 0; equal < 3; equal++)
		{
			if (board.coordinates[equal][equal] == my_letter) my_letter_count++;
			else if (board.coordinates[equal][equal] == UNOCCUPIED) available_move = move(equal, equal);
		}

		if (my_letter_count == 2)
		{
			winning_move = available_move;
			return WINNER_FOUND;
		}
	}

	if (board.diagonal_counter[1] == 2)
	{
		my_letter_count = 0;

		int alternate = 0;
		for (alternate; alternate < 3; alternate++)
		{
			if (board.coordinates[alternate][2 - alternate] == my_letter) my_letter_count++;
			else if (board.coordinates[alternate][2 - alternate] == UNOCCUPIED) available_move = move(alternate, 2 - alternate);
		}

		if (my_letter_count == 2)
		{
			winning_move = available_move;
			return WINNER_FOUND;
		}
	}

	return NOT_FOUND;
}

int AI::FindWinningMove(move& winning_move, const TicTacToe::Board& board, const letter& my_letter)
{
	if (FindWinningMoveInRows(winning_move, board, my_letter) == WINNER_FOUND) return WINNER_FOUND;

	if (FindWinningMoveInCols(winning_move, board, my_letter) == WINNER_FOUND) return WINNER_FOUND;

	if (FindWinningMoveInDiagonals(winning_move, board, my_letter) == WINNER_FOUND) return WINNER_FOUND;

	return NOT_FOUND;
}

move AI::PreventLoss(const TicTacToe::Board& board) const
{
	letter opponent_letter = TicTacToe::GetOpponentLetter();

	move opponent_winning_move(-33, -33);

	FindWinningMove(opponent_winning_move, board, opponent_letter);
	
	return opponent_winning_move;
}

move AI::FindWinOrMakeRandomMove(const TicTacToe::Board& board) const
{
	letter my_letter = TicTacToe::GetActiveLetter();

	move winning_move(-33, -33);

	if (FindWinningMove(winning_move, board, my_letter) == WINNER_FOUND) return winning_move;

	else return MakeRandomMove();
}


move AI::FindWinOrPreventLossOrMakeRandomMove(const TicTacToe::Board& board) const
{
	letter my_letter = TicTacToe::GetActiveLetter();

	move winning_move(-33, -33);

	if (FindWinningMove(winning_move, board, my_letter) == WINNER_FOUND) return winning_move;

	letter opponent_letter = TicTacToe::GetOpponentLetter();

	move opponent_winning_move(-33, -33);

	if (FindWinningMove(opponent_winning_move, board, opponent_letter) == WINNER_FOUND) return opponent_winning_move;

	else return MakeRandomMove();
}

int AI::Min(const int* const& scores, const int& length)
{
	int min_value = 10;

	for (int i = 0; i < length; i++)
	{
		if (scores[i] < min_value) min_value = scores[i];
	}

	return min_value;
}

int AI::Max(const int* const& scores, const int& length)
{
	int max_value = -10;

	for (int i = 0; i < length; i++)
	{
		if (scores[i] > max_value) max_value = scores[i];
	}

	return max_value;
}

int AI::FindMax(const int* const& scores, const int& length)
{
	int max = Max(scores, length);

	int max_index = 0;

	for (int i = 0; i < length; i++)
	{
		if (scores[i] == max) max_index = i;
	}

	return max_index;
}

int AI::MinMaxScore(const move& last_move, const TicTacToe::Board& board, const int& last_letter)
{
	letter my_letter = TicTacToe::GetActiveLetter();

	if (board.CheckState(last_move) == GAME_END)
	{
		if (last_letter == my_letter) return 10;
		else return -10;
	}

	if (board.isFull()) return 0;

	letter this_letter = (last_letter == O) ? X : O;

	move* valid_moves = board.GetValidMoves();

	int* moves_scores = new int[board.nr_of_available_moves];

	// Get scores of available moves
	for (int index = 0; index < board.nr_of_available_moves; index++)
	{
		TicTacToe::Board new_board = board;

		new_board.Mark(valid_moves[index].x, valid_moves[index].y, this_letter);

		int score = MinMaxScore(valid_moves[index], new_board, this_letter);

		moves_scores[index] = score;
	}

	int best_score;

	if (last_letter == my_letter) best_score = Min(moves_scores, board.nr_of_available_moves);

	else best_score = Max(moves_scores, board.nr_of_available_moves);

	delete[] valid_moves;

	delete[] moves_scores;

	return best_score;
}

move AI::MinMaxMove(const TicTacToe::Board& board) const
{
	letter my_letter = TicTacToe::GetActiveLetter();

	int* moves_scores = new int[board.nr_of_available_moves];

	// Get scores of available moves
	for (int index = 0; index < board.nr_of_available_moves; index++)
	{
		TicTacToe::Board new_board = board;

		new_board.Mark(m_valid_moves[index].x, m_valid_moves[index].y, my_letter);

		int score = MinMaxScore(m_valid_moves[index], new_board, my_letter);

		moves_scores[index] = score;
	}

	// If defeat is inevitable (i.e. every move leads to a defeat), then delay it as much as possible
	if (Max(moves_scores, board.nr_of_available_moves) == -10) return PreventLoss(board);

	int max_score_index = FindMax(moves_scores, board.nr_of_available_moves);

	delete[] moves_scores;

	return m_valid_moves[max_score_index];
}

move AI::MakeMove(TicTacToe::Board board) const
{
	return (this->*Difficulty)(board);
}

AI* AI::CreatePlayer(const char* const& name, const difficulty& difficulty)
{
	return new AI(name, difficulty);
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