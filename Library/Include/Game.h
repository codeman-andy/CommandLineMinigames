#pragma once

// Imports the Game-interface
#include "IGame.h"

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

class Game : public IGame {
public:
	/* Gameboard */
	template <unsigned int x, unsigned int y>
	struct Board;

	typedef void (Game::*Gamemode)();

	/* Variables */
	state STATE;
	Gamemode m_Gamemode;
	Player* Players[2];
	int Active;
	int Opponent;

	/* Constructor*/
	Game();

	/* Destructor */
	virtual ~Game();
};