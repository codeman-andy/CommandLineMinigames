#include "Game/Battleship.h"

Game* Battleship::GetInstance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = new Battleship();
	}

	return s_Instance;
}