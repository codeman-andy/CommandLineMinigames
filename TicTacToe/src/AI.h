#pragma once

#include "Player.h"
#include "TicTacToe.h"

class AI : public Player {
	 move* m_valid_moves;
	 size_t m_nr_of_valid_moves;
	 size_t FindMoveIndex(move move) const;
	 void DecrementValidMoves(size_t index);
public:
	AI(const char* name);
	void SetValidMoves(size_t dimensions_lengths[]);
	void RemoveFromValidMoves(move move);
	move MakeRandomMove() const;
	static int FindWinningMoveInRows(move& winning_move, size_t board[3][3], size_t row_count[3], size_t my_letter);
	static int FindWinningMoveInCols(move& winning_move, size_t board[3][3], size_t col_count[3], size_t my_letter);
	static int FindWinningMoveInDiagonals(move& winning_move, size_t board[3][3], size_t diagonal_count[2], size_t my_letter);
	static int FindWinningMove(move& winning_move, size_t board[3][3], size_t row_count[3], size_t col_count[3], size_t diagonal_count[2]);
	move FindWinOrMakeRandomMove(size_t board[3][3], size_t row_count[3], size_t col_count[3], size_t diagonal_count[2]) const;
	static AI* CreatePlayer(const char* name);
};