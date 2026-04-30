#include "Game.h"

Game* Game::s_Instance;

Game::Game() : m_State(RUNNING), m_Gamemode(nullptr), Players({ nullptr }), Active(UNASSIGNED), Opponent(UNASSIGNED) {}

Game::~Game()
{
	delete s_Instance;

	delete Players[0];
	delete Players[1];
}