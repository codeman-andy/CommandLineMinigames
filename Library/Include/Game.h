#pragma once

// Imports the game settings
#include "Settings.h"

// Imports Player-class
#include "Player.h"

// Imports Printable-interface
#include "Printable.h"

/*
 * The Game-superclass that all minigames will inherit
 * There will always only be one Game-instance at any given moment
 * Each game will present a state between RUNNING, WINNER_FOUND, or DRAW
 */

struct Game {
	/* Gameboard */
	template <unsigned int x, unsigned int y>
	struct Board;

	/* Variables */
	static state STATE;
	static void (*Gamemode)();
	static Player* Players[2];
	static int Active;
	static int Opponent;

	/* Constructor*/
	Game();

	/* Interface */
	virtual void PrintVictoryMessage() const = 0;
	virtual void PrintWelcomeMessage() const = 0;
};