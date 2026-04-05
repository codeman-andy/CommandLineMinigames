#include "Battleship.h"

struct Battleship::Board {
	int coordinates[9][11];
	int row_counter[9];
	int col_counter[11];
	int nr_of_available_moves;

	Board() : coordinates({ UNOCCUPIED }), row_counter({ EMPTY }), col_counter({ EMPTY }), nr_of_available_moves(99) {};

	Board(int coordinates[3][3], int rows_counters[3], int cols_counters[3], int nr_of_available_moves) {
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				this->coordinates[col][row] = coordinates[col][row];
			}
		}

		for (int counter_index = 0; counter_index < 9; counter_index++) {
			this->row_counter[counter_index] = rows_counters[counter_index];
			this->col_counter[counter_index] = cols_counters[counter_index];
		}
		this->col_counter[9] = cols_counters[9];
		this->col_counter[10] = cols_counters[10];

		this->nr_of_available_moves = nr_of_available_moves;
	}
};