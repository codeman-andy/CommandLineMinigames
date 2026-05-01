#include "Game.h"

Game* Game::s_Instance;

Game* Game::GetInstance()
{
	if (s_Instance == nullptr)
	{
		Log("There is no game currently going on.\n");
	}

	return s_Instance;
}