#pragma once

#include "Player.h"
#include "TicTacToe.h"

struct move {
	coords position;
	bool valid;
};

class AI : public Player {
	 move* m_valid_moves;
	 size_t m_nr_of_valid_moves;
public:
	AI(const char* name);
	static coords DecideMove(size_t board[3][3], size_t rows[3], size_t cols[3], size_t diagonals[2], letter my_letter);
	void SetValidMoves(size_t dimensions_lengths[]);
	void RemoveValidMove(coords move);
	coords MakeRandomMove();
};