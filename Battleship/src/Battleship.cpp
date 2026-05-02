#include "Battleship.h"


Battleship* Battleship::GetInstance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = new Battleship();
	}

	return static_cast<Battleship*>(s_Instance);
}