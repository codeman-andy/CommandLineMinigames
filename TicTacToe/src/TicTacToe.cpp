#include "TicTacToe.h"


TicTacToe* TicTacToe::GetInstance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = new TicTacToe();
	}

	return static_cast<TicTacToe*>(s_Instance);
}