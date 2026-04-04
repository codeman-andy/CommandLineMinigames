#pragma once

#include "Settings.h"

struct Game {
	static state STATE;
	Game();
	virtual void PrintVictoryMessage() const = 0;
	static void PrintWelcomeMessage();
};