#include "Battleship.h"

void PlayBattleship() {
	Battleship GAME = Battleship::Start();

	Battleship::Loop();

	GAME.End();
}

int main()
{
	int command = 1;
	while (command)
	{
		PlayBattleship();
		clear_buffer();

		Log("Would you like to play again?\n");
		Log("1. Yes [0. Exit]\n");
		std::cin >> command;
	}

	std::cin.get();
}