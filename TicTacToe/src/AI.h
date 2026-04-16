#pragma once

#include "TicTacToe.h"

/*
 * AI is a public sub-class of the Player-class.
 * AI adds a new parameter to the Player-class : difficulty.
 * It has pre-determined name conventions for each difficulty.
 * It determines which algorithm (i.e. method-member) it will use to choose a move based on the difficulty parameter it was instantiated with:
 * 
 * EASY :
 *   TicTacToe : The AI will make a winning move, otherwise a random move
 * MEDIUM :
 *   TicTacToe : The AI will make a winning move, otherwise prevent the opponent to win, otherwise a random move
 * EXPERT :
 *   TicTacToe : The AI applies a minmax-algorithm to choose its next move
 *               (if there are no good moves left, it will prevent the opponent to win or otherwise make a random move)
 * 
 */

class AI : public Player {
	/* Variables */
	difficulty m_difficulty;
	move (AI::* Difficulty)(const TicTacToe::Board&) const;
	move* m_valid_moves;
	int m_nr_of_valid_moves;

	/* Constructor */
	AI(const char* const& name, const difficulty& difficulty);

	/* Methods */
	int FindMoveIndex(const move& move) const;
	void DecrementValidMoves(int index);
	move& MakeRandomMove() const;
	static int FindWinningMoveInRows(move& winning_move, const TicTacToe::Board& board, const letter& my_letter);
	static int FindWinningMoveInCols(move& winning_move, const TicTacToe::Board& board, const letter& my_letter);
	static int FindWinningMoveInDiagonals(move& winning_move, const TicTacToe::Board& board, const letter& my_letter);
	static int FindWinningMove(move& winning_move, const TicTacToe::Board& board, const letter& my_letter);
	static int Min(const int* const& scores, const int& length);
	static int Max(const int* const& scores, const int& length);
	static int FindMax(const int* const& scores, const int& length);
	static int MinMaxScore(const move& last_move, const TicTacToe::Board& board, const int& last_letter);
	move PreventLoss(const TicTacToe::Board& board) const;
	move FindWinOrMakeRandomMove(const TicTacToe::Board& board) const;
	move FindWinOrPreventLossOrMakeRandomMove(const TicTacToe::Board& board) const;
	move MinMaxMove(const TicTacToe::Board& board) const;

public:
	/* Interface */
	void SetDifficulty(const difficulty& difficulty);
	void SetValidMoves(move* const& valid_moves, const int& nr_of_valid_moves);
	void RemoveFromValidMoves(const move& move);
	move MakeMove(TicTacToe::Board board) const;
	static AI* CreatePlayer(const char* const& name, const difficulty& difficulty);
};