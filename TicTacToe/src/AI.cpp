#include "AI.h"

coords AI::DecideMove() {
	size_t nice_row = 0;
	size_t nice_col = 0;
	for (int i = 0; i < 3; i++) {
		if (TicTacToe::rows[i] >= nice_row && TicTacToe::rows[i] < FULL) nice_row = i;
	}
	for (int j = 0; j < 3; j++) {
		if (TicTacToe::board[nice_row][j] == UNOCCUPIED) nice_col = j;
	}
	coords decision;
	decision.x = nice_col;
	decision.y = nice_row;
	std::cout << "Pam decided: [" << decision.y << ", " << decision.x << "]" << std::endl;
	return decision;
}