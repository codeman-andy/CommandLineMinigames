#include "TicTacToe.h"

void PlayTicTacToe()
{
	TicTacToe GAME = TicTacToe::Start();

	TicTacToe::Loop();

	GAME.End();
}

int main()
{
	bool isRunning = true;
	int ProgramState = isRunning;
	while (ProgramState == isRunning)
	{
		PlayTicTacToe();
		clear_buffer();

		Log("Would you like to play again?\n");
		Log("1. Yes [0. Exit]\n");
		std::cin >> ProgramState;
	}

	std::cin.get();
}