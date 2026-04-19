#pragma once

// Imports the parent-class
#include "Player.h"


/*
 * Human_Player is a public sub-class of the Player-class
 * The main feature of this class is that its name is user-input designated
 */

class Human_Player : public Player {
public:
	/* Interface */
	static Human_Player* CreatePlayer();
};