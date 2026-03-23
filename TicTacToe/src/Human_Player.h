#pragma once

#include "Player.h"

class Human_Player : public Player {
public:
	static const char* GetPlayerNameFromInput();
	static Human_Player* CreatePlayer();
};