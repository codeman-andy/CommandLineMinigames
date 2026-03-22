#pragma once

#include "Log.h"

class Player {
	const char* m_name;
public:
	Player(const char* name);

	const char* GetName() const;

	static const char* GetPlayerNameFromInput();

	static Player* CreatePlayer();
};