#pragma once

#include "Settings.h"

struct Game {
	static state STATE;
	Game();
	virtual void PrintVictoryMessage() = 0;
	static void PrintWelcomeMessage();
};