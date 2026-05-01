#pragma once

#include "Player.h"

class PlayerFactory {
public:
	virtual Player* CreatePlayer() = 0;
};