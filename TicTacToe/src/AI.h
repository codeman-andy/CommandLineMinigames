#pragma once

#include "Player.h"
#include "TicTacToe.h"

class AI : public Player {
public:
	static coords DecideMove();
};