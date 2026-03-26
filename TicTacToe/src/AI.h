#pragma once

#include "Player.h"
#include "TicTacToe.h"

class AI : public Player {
public:
	static coords DecideMove(size_t board[3][3], size_t rows[3], size_t cols[3], size_t diagonals[2], letter my_letter);
};