#include "TicTacToe.h"

TicTacToe GAME = TicTacToe();

int main() {
	TicTacToe::PrintWelcomeMessage();

	GAME.SetUpGame();

	while (GAME.STATE == RUNNING) {
		TicTacToe::TakeTurn();
	}
	TicTacToe::PrintBoard();

	if (GAME.STATE == DRAW) TicTacToe::PrintDrawMessage();

	else GAME.PrintVictoryMessage();

	clear_buffer();
	std::cin.get();
}