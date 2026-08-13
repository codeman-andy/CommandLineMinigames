#include "Game/Snake.h"

Game* Snake::GetInstance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = new Snake();
	}

	return s_Instance;
}