#include "CommandLineMinigames.h"

void PlayTicTacToe()
{
	Game* GAME = TicTacToe::GetInstance();

	GAME->Start();

	GAME->Loop();

	GAME->End();
}

void PlayGame(int game)
{
	Game* GAME = (game == 1) ? Battleship::GetInstance()
			   : (game == 2) ? TicTacToe::GetInstance()
			   : Snake::GetInstance();

	GAME->Start();

	GAME->Loop();

	GAME->End();
}

int PickGame()
{
	int choice;
	Log("Which game do you want to play?\n");
	Log("1. Battleship\n2. Tic-Tac-Toe\n");
	Log("Choose:");
	std::cin >> choice;
	return choice;
}

int main()
{
	bool isRunning = true;
	bool ProgramState = isRunning;
	while (ProgramState == isRunning)
	{
		int game = PickGame();
		clear_buffer();

		PlayGame(game);
		clear_buffer();

		Log("Would you like to play again?\n");
		Log("1. Yes [0. Exit]\n");
		std::cin >> ProgramState;
	}

	std::cin.get();
}