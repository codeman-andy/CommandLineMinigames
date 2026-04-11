#pragma once

// Imports the game settings
#include "Settings.h"


/*
 * The Game-superclass that all minigames will inherit
 * There will always only be one Game-instance at any given moment
 * Each game will present a state between RUNNING, WINNER_FOUND, or DRAW
 */

struct Game {
	/* Variables */
	static state STATE;

	/* Constructor*/
	Game();

	/* Interface */
	virtual void PrintVictoryMessage() const = 0;
	static void PrintWelcomeMessage();
};