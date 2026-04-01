#pragma once

#include "Player.h"
#include "TicTacToe.h"

class AI : public Player {
	/* Variables */
	difficulty m_difficulty;
	move (AI::* Difficulty)(ttt_board) const;
	move* m_valid_moves;
	int m_nr_of_valid_moves;

	/* Methods */
	int FindMoveIndex(move move) const;
	void DecrementValidMoves(int index);
	move MakeRandomMove() const;
	static int FindWinningMoveInRows(move& winning_move, ttt_board board, int my_letter);
	static int FindWinningMoveInCols(move& winning_move, ttt_board board, int my_letter);
	static int FindWinningMoveInDiagonals(move& winning_move, ttt_board board, int my_letter);
	static int FindWinningMove(move& winning_move, ttt_board board, int my_letter);
	static int Min(int* scores, int length);
	static int Max(int* scores, int length);
	static int FindMaxIndex(int* scores, int length);
	static int MinMaxScore(move& last_move, ttt_board board, int last_letter);
	move FindWinOrMakeRandomMove(ttt_board board) const;
	move FindWinOrPreventLossOrMakeRandomMove(ttt_board board) const;
	move MinMaxMove(ttt_board board) const;
public:
	AI(const char* name, difficulty difficulty);
	void SetDifficulty(difficulty difficulty);
	void SetValidMoves(move* valid_moves, int nr_of_valid_moves);
	void RemoveFromValidMoves(move move);
	move MakeMove(ttt_board board) const;
	static AI* CreatePlayer(const char* name, difficulty difficulty);
};