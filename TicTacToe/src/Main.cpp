#include "Log.h"
#include "Player.h"
#include "TicTacToe.h"

TicTacToe GAME = TicTacToe();

int main() {
	TicTacToe::PrintWelcomeMessage();

	GAME.SetUpGame();

	GAME.SetUpTurn();

	GAME.PrintBoard();
	while (GAME.game_state == RUNNING) {
		if (TicTacToe::current_turn() != WINNER_FOUND) GAME.SetUpTurn();
		GAME.PrintBoard();
	}
	GAME.PrintVictoryMessage();

	clear_buffer();
	std::cin.get();
}