#pragma once

// Imports 'std::getline()' method to read users' names with whitespaces
#include <string>

// Imports the parent-class
#include "Player.h"


/*
 * Human_Player is a public sub-class of the Player-class
 * The main feature of this class is that its name is user-input designated
 */

class HumanPlayer : public Player {
public:
	/* Constructor */
	HumanPlayer(const char* name) : Player(name)
	{}
};