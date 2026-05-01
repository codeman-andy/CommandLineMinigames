#pragma once

#include "BoardTicTacToe.h"

#include "Move.h"

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
	/* Variables */
	Move* m_valid_moves;
	unsigned int m_nr_of_valid_moves;
	Difficulty m_difficulty;
	Move (AI::* m_algorithm)(const Board&) const;

	/* Methods */
	unsigned int FindMoveIndex(const Move& Move) const;
	void DecrementValidMoves(unsigned int index);
	Move& MakeRandomMove() const;
	static int FindWinningMoveInRows(Move& winning_move, const Board& board, const Letter& my_letter);
	static int FindWinningMoveInCols(Move& winning_move, const Board& board, const Letter& my_letter);
	static int FindWinningMoveInDiagonals(Move& winning_move, const Board& board, const Letter& my_letter);
	static int FindWinningMove(Move& winning_move, const Board& board, const Letter& my_letter);
	static int Min(const int* const& scores, const int& length);
	static int Max(const int* const& scores, const int& length);
	static int FindMax(const int* const& scores, const int& length);
	static int MinMaxScore(const Move& last_move, const Board& board, const int& last_letter);
	Move PreventLoss(const Board& board) const;
	Move FindWinOrMakeRandomMove(const Board& board) const;
	Move FindWinOrPreventLossOrMakeRandomMove(const Board& board) const;
	Move MinMaxMove(const Board& board) const;

public:
	/* Constructor */
	AI(const Difficulty& difficulty);

	/* Interface */
	void SetDifficulty(const Difficulty& difficulty);
	void SetValidMoves(Move* const& valid_moves, const int& nr_of_valid_moves);
	void RemoveFromValidMoves(const Move& Move);
	Move MakeMove(Board board) const;
	static AI* CreatePlayer(const Difficulty& difficulty);
};