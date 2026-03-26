#pragma once

#include "Player.h"

class Human_Player : public Player {
	static const char* GetPlayerNameFromInput();
public:
	static Human_Player* CreatePlayer();
};