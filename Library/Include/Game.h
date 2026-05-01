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
public:
	/* Get singleton-instance */
	static Game* GetInstance();

protected:
	/* Function-pointer to either the PvP or the PvE gamemode */
	typedef void (Game::*Gamemode)();

	/* Singleton-instance */
	static Game* s_Instance;

	/* Variables */
	State a_State;
	Gamemode a_Gamemode;
	Player* a_Players[2];
	int a_Active;
	int a_Opponent;

	/* Constructor*/
	Game() : a_State(RUNNING),
			 a_Gamemode(nullptr),
			 a_Players({ nullptr }),
			 a_Active(UNASSIGNED),
			 a_Opponent(UNASSIGNED)
	{}

	/* Destructor */
	virtual ~Game()
	{
		delete s_Instance;

		delete a_Players[0];
		delete a_Players[1];
	}
};