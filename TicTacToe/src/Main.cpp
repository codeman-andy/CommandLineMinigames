#include "TicTacToe.h"

void PlayTicTacToe() {
	TicTacToe GAME = TicTacToe::Start();

	TicTacToe::Loop();

	GAME.End();
}

int main() {
	PlayTicTacToe();
	clear_buffer();
	std::cin.get();
}