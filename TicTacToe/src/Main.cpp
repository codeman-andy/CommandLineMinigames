#include "TicTacToe.h"

void PlayTicTacToe() {
	TicTacToe GAME = TicTacToe::Start();

	TicTacToe::Loop();

	GAME.End();
}

int main() {

	int command = 1;

	while (command) {
		PlayTicTacToe();
		clear_buffer();

		Log("Would you like to play again?\n");
		Log("1. Yes [0. Exit]\n");
		std::cin >> command;
	}

	std::cin.get();
}