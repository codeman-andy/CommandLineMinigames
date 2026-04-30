#pragma once

// Imports the Game-interface
#include "IGame.h"

// Imports the game settings
#include "Settings.h"

// Imports Player-class
#include "Player.h"

// Imports IPrintable-interface
#include "IPrintable.h"

/*
 * The Game-superclass that all minigames will inherit
 * There will always only be one Game-instance at any given moment
 * Each game will present a State between RUNNING, WINNER_FOUND, or DRAW
 */

class Game : public IGame {
protected:
	/* Function-pointer to either the PvP or the PvE gamemode */
	typedef void (Game::*Gamemode)();

	/* Singleton-instance */
	static Game* s_Instance;

	/* Variables */
	State m_State;
	Gamemode m_Gamemode;
	Player* Players[2];
	int Active;
	int Opponent;

	/* Constructor*/
	Game();

	/* Destructor */
	virtual ~Game();
};