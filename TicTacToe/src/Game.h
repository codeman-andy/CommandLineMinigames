#pragma once

#include "Settings.h"

/*
 + The Game-superclass that all minigames will inherit
 + There will always only be one Game-instance at any given moment
 + Each game will present a state between RUNNING, WINNER_FOUND, or DRAW
*/
struct Game {
	static state STATE;
	Game();
	virtual void PrintVictoryMessage() const = 0;
	static void PrintWelcomeMessage();
};