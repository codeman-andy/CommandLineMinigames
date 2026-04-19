#pragma once

// Imports <iostream> to be able to accept user-input
#include "Log.h"


/*
 * The Player-superclass that all player-variants will inherit.
 * Every Player-instance must possess a name.
 */

class Player {
public:
	/* Variables */
	const char* m_name;

	/* Constructors */
	Player();
	Player(const char* const& name);

	/* Methods */
	static const char* GetPlayerNameFromInput();

	/* Interface */
	const char* GetName() const;
	static Player* CreatePlayer(const char* name);
};