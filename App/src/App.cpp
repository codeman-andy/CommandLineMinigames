extern TicTacToe* TicTacToe::GetInstance();

void PlayTicTacToe()
{
	Game* GAME = TicTacToe::GetInstance();

	GAME->Start();

	GAME->Loop();

	GAME->End();
}

int main()
{
	bool isRunning = true;
	bool ProgramState = isRunning;
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