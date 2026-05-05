#include "Game/TicTacToe.h"

Game* TicTacToe::GetInstance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = new TicTacToe();
	}

	return s_Instance;
}