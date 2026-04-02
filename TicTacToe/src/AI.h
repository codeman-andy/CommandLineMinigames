#pragma once

#include "Player.h"
#include "TicTacToe.h"

class AI : public Player {
	/* Variables */
	difficulty m_difficulty;
	move (AI::* Difficulty)(const TicTacToe::ttt_board&) const;
	move* m_valid_moves;
	int m_nr_of_valid_moves;

	/* Methods */
	int FindMoveIndex(const move& move) const;
	void DecrementValidMoves(int index);
	move MakeRandomMove() const;
	static int FindWinningMoveInRows(move& winning_move, const TicTacToe::ttt_board& board, const int& my_letter);
	static int FindWinningMoveInCols(move& winning_move, const TicTacToe::ttt_board& board, const int& my_letter);
	static int FindWinningMoveInDiagonals(move& winning_move, const TicTacToe::ttt_board& board, const int& my_letter);
	static int FindWinningMove(move& winning_move, const TicTacToe::ttt_board& board, const int& my_letter);
	static int Min(const int* const& scores, const int& length);
	static int Max(const int* const& scores, const int& length);
	static int FindMaxIndex(const int* const& scores, const int& length);
	static int MinMaxScore(const move& last_move, const TicTacToe::ttt_board& board, const int& last_letter);
	move FindWinOrMakeRandomMove(const TicTacToe::ttt_board& board) const;
	move FindWinOrPreventLossOrMakeRandomMove(const TicTacToe::ttt_board& board) const;
	move MinMaxMove(const TicTacToe::ttt_board& board) const;
public:
	AI(const char* const& name, const difficulty& difficulty);
	void SetDifficulty(const difficulty& difficulty);
	void SetValidMoves(move* const& valid_moves, const int& nr_of_valid_moves);
	void RemoveFromValidMoves(const move& move);
	move MakeMove(TicTacToe::ttt_board board) const;
	static AI* CreatePlayer(const char* const name, const difficulty& difficulty);
};