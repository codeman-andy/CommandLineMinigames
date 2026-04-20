#include "Battleship.h"

void PlayBattleship()
{
	Battleship GAME = Battleship::Start();

	GAME.Loop();

	GAME.End();
}

int main()
{
	bool isRunning = true;
	bool ProgramState = isRunning;
	while (ProgramState == isRunning)
	{
		PlayBattleship();
		clear_buffer();

		Log("Would you like to play again?\n");
		Log("1. Yes [0. Exit]\n");
		std::cin >> ProgramState;
	}

	std::cin.get();
}