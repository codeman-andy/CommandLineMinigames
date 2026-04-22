#include "Game.h"

Game::Game() : m_State(RUNNING), m_Gamemode(nullptr), Players({ nullptr }), Active(UNASSIGNED), Opponent(UNASSIGNED) {}

Game::~Game()
{
	delete Players[0];
	delete Players[1];
}