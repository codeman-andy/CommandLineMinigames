#pragma once

#include "Log.h"

class Player {
public:
	const char* m_name;
	Player();
	Player(const char* name);

	const char* GetName() const;

	static Player* CreatePlayer(const char* name);
};