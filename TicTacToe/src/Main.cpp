#include "TicTacToe.h"

TicTacToe GAME = TicTacToe();

int main() {
	TicTacToe::PrintWelcomeMessage();

	GAME.SetUpGame();

	TicTacToe::PrintBoard();
	while (GAME.STATE == RUNNING) {
		TicTacToe::TakeTurn();
		TicTacToe::PrintBoard();
	}
	GAME.PrintVictoryMessage();

	clear_buffer();
	std::cin.get();
}