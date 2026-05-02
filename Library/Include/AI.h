#pragma once

#include "BoardTicTacToe.h"

#include "Move.h"

#include "Game.h"

#include "Player.h"

#include "Settings.h"

/*
 * AI is a public sub-class of the Player-class.
 * AI adds a new parameter to the Player-class : Difficulty.
 * It has pre-determined name conventions for each Difficulty.
 * It determines which algorithm (i.e. method-member) it will use to choose a Move based on the Difficulty parameter it was instantiated with:
 * 
 * EASY :
 *   TicTacToe : The AI will make a winning Move, otherwise a random Move
 * MEDIUM :
 *   TicTacToe : The AI will make a winning Move, otherwise prevent the opponent to win, otherwise a random Move
 * EXPERT :
 *   TicTacToe : The AI applies a minmax-algorithm to choose its next Move
 *               (if there are no good moves left, it will prevent the opponent to win or otherwise make a random Move)
 * 
 */

class AI : public Player {
public:
	/* Constructor */
	AI(const Difficulty& difficulty) : m_valid_moves(nullptr),
		m_nr_of_valid_moves(NULL),
		m_difficulty(difficulty)
	{
		m_name = (m_difficulty == EASY) ? "Pam"
			: (m_difficulty == MEDIUM) ? "Donald J. Trump"
			: "Peter Thiel";

		m_algorithm = (m_difficulty == EASY) ? &AI::FindWinOrMakeRandomMove
			: (m_difficulty == MEDIUM) ? &AI::FindWinOrPreventLossOrMakeRandomMove
			: &AI::MinMaxMove;
	}

	/* Interface */
	void SetDifficulty(const Difficulty& difficulty) { m_difficulty = difficulty; }

	void SetValidMoves(Move* const& valid_moves, const int& nr_of_valid_moves)
	{
		m_valid_moves = valid_moves;
		m_nr_of_valid_moves = nr_of_valid_moves;
	}

	void RemoveFromValidMoves(const Move& move)
	{
		unsigned int index = FindMoveIndex(move);

		DecrementValidMoves(index);
	}

	Move MakeMove(Board board) const
	{
		return (this->*m_algorithm)(board);
	}

private:
	/* Variables */
	Move* m_valid_moves;
	unsigned int m_nr_of_valid_moves;
	Difficulty m_difficulty;
	Move (AI::* m_algorithm)(const Board&) const;

	/* Static Methods */
	static int FindWinningMoveInRows(Move& winning_move, const Board& board, const Letter& my_letter);
	static int FindWinningMoveInCols(Move& winning_move, const Board& board, const Letter& my_letter);
	static int FindWinningMoveInDiagonals(Move& winning_move, const Board& board, const Letter& my_letter);
	static int FindWinningMove(Move& winning_move, const Board& board, const Letter& my_letter);
	static int Min(const int* const& scores, const int& length);
	static int Max(const int* const& scores, const int& length);
	static int FindMax(const int* const& scores, const int& length);
	static int MinMaxScore(const Move& last_move, const Board& board, const int& last_letter);

	/* Member Methods */
	unsigned int FindMoveIndex(const Move& move) const
	{
		unsigned int index = 0;

		while (m_valid_moves[index] != move) index++;

		return index;
	}

	void DecrementValidMoves(unsigned int index)
	{
		m_nr_of_valid_moves--;

		for (index; index < m_nr_of_valid_moves; index++) m_valid_moves[index] = m_valid_moves[index + 1];
	}

	Move& MakeRandomMove() const
	{
		int random_index = rand() % (m_nr_of_valid_moves - 1);

		return m_valid_moves[random_index];
	}

	Move PreventLoss(const Board& board) const
	{
		Letter opponent_letter = Game::GetInstance()->GetOpponentLetter();

		Move opponent_winning_move(-33, -33);

		FindWinningMove(opponent_winning_move, board, opponent_letter);

		return opponent_winning_move;
	}

	Move FindWinOrMakeRandomMove(const Board& board) const
	{
		Letter my_letter = Game::GetInstance()->GetActiveLetter();

		Move winning_move(-33, -33);

		if (FindWinningMove(winning_move, board, my_letter) == WINNER_FOUND) return winning_move;

		else return MakeRandomMove();
	}

	Move FindWinOrPreventLossOrMakeRandomMove(const Board& board) const
	{
		Letter my_letter = Game::GetInstance()->GetActiveLetter();

		Move winning_move(-33, -33);

		if (FindWinningMove(winning_move, board, my_letter) == WINNER_FOUND) return winning_move;

		Letter opponent_letter = Game::GetInstance()->GetOpponentLetter();

		Move opponent_winning_move(-33, -33);

		if (FindWinningMove(opponent_winning_move, board, opponent_letter) == WINNER_FOUND) return opponent_winning_move;

		else return MakeRandomMove();
	}

	Move MinMaxMove(const Board& board) const
	{
		Letter my_letter = Game::GetInstance()->GetActiveLetter();

		int* moves_scores = new int[board.nr_of_available_moves];

		// Get scores of available moves
		for (int index = 0; index < board.nr_of_available_moves; index++)
		{
			Board new_board = board;

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
};