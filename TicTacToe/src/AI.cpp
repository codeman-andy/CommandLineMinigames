#include "AI.h"

#include "TicTacToeBoard.cpp"

AI::AI(const Difficulty& difficulty) : m_valid_moves(nullptr), m_nr_of_valid_moves(NULL), m_difficulty(difficulty)
{
	m_name = (m_difficulty == EASY) ? "Pam"
		   : (m_difficulty == MEDIUM) ? "Donald J. Trump"
		   : "Peter Thiel";

	m_algorithm = (m_difficulty == EASY) ? &AI::FindWinOrMakeRandomMove
			   : (m_difficulty == MEDIUM) ? &AI::FindWinOrPreventLossOrMakeRandomMove
			   : &AI::MinMaxMove;
}

void AI::SetDifficulty(const Difficulty& difficulty)
{
	m_difficulty = difficulty;
}

unsigned int AI::FindMoveIndex(const Move& move) const
{
	unsigned int index = 0;
	while (m_valid_moves[index] != move)
	{
		index++;
	}
	return index;
}

void AI::DecrementValidMoves(unsigned int index)
{
	m_nr_of_valid_moves--;

	for (index; index < m_nr_of_valid_moves; index++) m_valid_moves[index] = m_valid_moves[index + 1];
}

void AI::SetValidMoves(Move* const& valid_moves, const int& nr_of_valid_moves)
{
	m_valid_moves = valid_moves;
	m_nr_of_valid_moves = nr_of_valid_moves;
}

void AI::RemoveFromValidMoves(const Move& move)
{
	unsigned int index = FindMoveIndex(move);

	DecrementValidMoves(index);
}

Move& AI::MakeRandomMove() const
{
	int random_index = rand() % (m_nr_of_valid_moves - 1);
	return m_valid_moves[random_index];
}

int AI::FindWinningMoveInRows(Move& winning_move, const TicTacToe::Board& board, const Letter& my_letter)
{
	int my_letter_count;
	Move available_move = Move();

	for (int row = 0; row < 3; row++)
	{
		if (board.row_counter[row] != 2) continue;

		my_letter_count = 0;
		for (int col = 0; col < 3; col++)
		{
			if (board.coordinates[col][row] == my_letter) my_letter_count++;
			else if (board.coordinates[col][row] == UNOCCUPIED) available_move = Move(col, row);
		}

		if (my_letter_count == 2)
		{
			winning_move = available_move;
			return WINNER_FOUND;
		}
	}

	return NOT_FOUND;
}

int AI::FindWinningMoveInCols(Move& winning_move, const TicTacToe::Board& board, const Letter& my_letter)
{
	int my_letter_count;
	Move available_move = Move();

	for (int col = 0; col < 3; col++)
	{
		if (board.col_counter[col] != 2) continue;

		my_letter_count = 0;
		for (int row = 0; row < 3; row++)
		{
			if (board.coordinates[col][row] == my_letter) my_letter_count++;
			else if (board.coordinates[col][row] == UNOCCUPIED) available_move = Move(col, row);
		}

		if (my_letter_count == 2)
		{
			winning_move = available_move;
			return WINNER_FOUND;
		}
	}

	return NOT_FOUND;
}

int AI::FindWinningMoveInDiagonals(Move& winning_move, const TicTacToe::Board& board, const Letter& my_letter)
{
	int my_letter_count;
	Move available_move = Move();

	if (board.diagonal_counter[0] == 2)
	{
		my_letter_count = 0;
		for (int equal = 0; equal < 3; equal++)
		{
			if (board.coordinates[equal][equal] == my_letter) my_letter_count++;
			else if (board.coordinates[equal][equal] == UNOCCUPIED) available_move = Move(equal, equal);
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
			else if (board.coordinates[alternate][2 - alternate] == UNOCCUPIED) available_move = Move(alternate, 2 - alternate);
		}

		if (my_letter_count == 2)
		{
			winning_move = available_move;
			return WINNER_FOUND;
		}
	}

	return NOT_FOUND;
}

int AI::FindWinningMove(Move& winning_move, const TicTacToe::Board& board, const Letter& my_letter)
{
	if (FindWinningMoveInRows(winning_move, board, my_letter) == WINNER_FOUND) return WINNER_FOUND;

	if (FindWinningMoveInCols(winning_move, board, my_letter) == WINNER_FOUND) return WINNER_FOUND;

	if (FindWinningMoveInDiagonals(winning_move, board, my_letter) == WINNER_FOUND) return WINNER_FOUND;

	return NOT_FOUND;
}

Move AI::PreventLoss(const TicTacToe::Board& board) const
{
	Letter opponent_letter = TicTacToe::GetOpponentLetter();

	Move opponent_winning_move(-33, -33);

	FindWinningMove(opponent_winning_move, board, opponent_letter);
	
	return opponent_winning_move;
}

Move AI::FindWinOrMakeRandomMove(const TicTacToe::Board& board) const
{
	Letter my_letter = TicTacToe::GetActiveLetter();

	Move winning_move(-33, -33);

	if (FindWinningMove(winning_move, board, my_letter) == WINNER_FOUND) return winning_move;

	else return MakeRandomMove();
}


Move AI::FindWinOrPreventLossOrMakeRandomMove(const TicTacToe::Board& board) const
{
	Letter my_letter = TicTacToe::GetActiveLetter();

	Move winning_move(-33, -33);

	if (FindWinningMove(winning_move, board, my_letter) == WINNER_FOUND) return winning_move;

	Letter opponent_letter = TicTacToe::GetOpponentLetter();

	Move opponent_winning_move(-33, -33);

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

int AI::MinMaxScore(const Move& last_move, const TicTacToe::Board& board, const int& last_letter)
{
	Letter my_letter = TicTacToe::GetActiveLetter();

	if (board.CheckState(last_move) == GAME_END)
	{
		if (last_letter == my_letter) return 10;
		else return -10;
	}

	if (board.isFull()) return 0;

	Letter this_letter = (last_letter == O) ? X : O;

	Move* valid_moves = board.GetValidMoves();

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

Move AI::MinMaxMove(const TicTacToe::Board& board) const
{
	Letter my_letter = TicTacToe::GetActiveLetter();

	int* moves_scores = new int[board.nr_of_available_moves];

	// Get scores of available moves
	for (int index = 0; index < board.nr_of_available_moves; index++)
	{
		TicTacToe::Board new_board = board;

		new_board.Mark(m_valid_moves[index].x, m_valid_moves[index].y, my_letter);

		int score = MinMaxScore(m_valid_moves[index], new_board, my_letter);

		moves_scores[index] = score;
	}

	// If defeat is inevitable (i.e. every Move leads to a defeat), then delay it as much as possible
	if (Max(moves_scores, board.nr_of_available_moves) == -10) return PreventLoss(board);

	int max_score_index = FindMax(moves_scores, board.nr_of_available_moves);

	delete[] moves_scores;

	return m_valid_moves[max_score_index];
}

Move AI::MakeMove(TicTacToe::Board board) const
{
	return (this->*m_algorithm)(board);
}

AI* AI::CreatePlayer(const Difficulty& difficulty)
{
	return new AI(difficulty);
}

/* VERY PRIMITIVE, PROOF OF CONCEPT ATTEMPT AT AI
Move AI::DecideMove(int board[3][3], int rows[3], int cols[3], int diagonals[2], Letter my_letter) {
	Move decision = Move();
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