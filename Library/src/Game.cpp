#include "Game.h"

Game::Game() : STATE(RUNNING), m_Gamemode(nullptr), Players({ nullptr }), Active(UNASSIGNED), Opponent(UNASSIGNED) {}

Game::~Game()
{
	delete Players[0];
	delete Players[1];
}