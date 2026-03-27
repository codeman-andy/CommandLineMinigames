#pragma once

#include "Player.h"
#include "TicTacToe.h"

class AI : public Player {
	 move* m_valid_moves;
	 size_t m_nr_of_valid_moves;
public:
	AI(const char* name);
	static move DecideMove(size_t board[3][3], size_t rows[3], size_t cols[3], size_t diagonals[2], letter my_letter);
	void SetValidMoves(size_t dimensions_lengths[]);
	void RemoveFromValidMoves(move move);
	move MakeRandomMove();
	int FindWinningMove(move& winning_move, size_t board[3][3], size_t row_count[3], size_t col_count[3], size_t diagonal_count[2]);
	move WinOrMakeRandomMove(size_t board[3][3], size_t row_count[3], size_t col_count[3], size_t diagonal_count[2]);
	static AI* CreatePlayer(const char* name);
};