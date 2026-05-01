#pragma once

// Imports <iostream> to be able to accept user-input
#include "Log.h"


/*
 * The Player-superclass that all player-variants will inherit.
 * Every Player-instance must possess a name.
 */

class Player {
protected:
	/* Variables */
	const char* m_name;

	/* Constructors */
	Player() : m_name(nullptr)
	{}
	Player(const char* const& name) : m_name(name)
	{}

public:
	/* Interface */
	const char* GetName() const	{ return m_name; }
};