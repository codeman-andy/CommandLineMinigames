#include "AI.h"

coords AI::DecideMove() {
	size_t nice_row = 0;
	size_t nice_col = 0;
	for (int i = 0; i < 3; i++) {
		if (TicTacToe::rows[i] > nice_row && TicTacToe::rows[i] < FULL) nice_row = TicTacToe::rows[i];
	}
	for (int j = 0; j < 3; j++) {
		if (TicTacToe::cols[j] == UNOCCUPIED) nice_col = TicTacToe::cols[j];
	}
	coords decision;
	decision.x = nice_row;
	decision.y = nice_col;
	return decision;
}