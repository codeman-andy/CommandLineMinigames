#include "TicTacToe.h"

struct TicTacToe::Board {
	int coordinates[3][3];
	int row_counter[3];
	int col_counter[3];
	int diagonal_counter[2];
	int nr_of_available_moves;

	Board() : coordinates({ UNOCCUPIED }), row_counter({ EMPTY }), col_counter({ EMPTY }), diagonal_counter({ EMPTY }), nr_of_available_moves(9) {};

	Board(int coordinates[3][3], int rows_counters[3], int cols_counters[3], int diagonals_counters[2], int nr_of_available_moves) {
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				this->coordinates[col][row] = coordinates[col][row];
			}
		}

		for (int counter_index = 0; counter_index < 2; counter_index++) {
			this->row_counter[counter_index] = rows_counters[counter_index];
			this->col_counter[counter_index] = cols_counters[counter_index];
			this->diagonal_counter[counter_index] = diagonals_counters[counter_index];
		}
		this->row_counter[2] = rows_counters[2];
		this->col_counter[2] = cols_counters[2];

		this->nr_of_available_moves = nr_of_available_moves;
	}

	/*
	Board(const Board& other) : nr_of_available_moves(other.nr_of_available_moves) {
		memcpy(this->coordinates, other.coordinates, 9);
		memcpy(this->row_counter, other.row_counter, 3);
		memcpy(this->col_counter, other.col_counter, 3);
		memcpy(this->diagonal_counter, other.diagonal_counter, 2);
	}
	*/

	void CopyBoard(Board other) {
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				this->coordinates[col][row] = other.coordinates[col][row];
			}
		}

		for (int counter_index = 0; counter_index < 2; counter_index++) {
			this->row_counter[counter_index] = other.row_counter[counter_index];
			this->col_counter[counter_index] = other.col_counter[counter_index];
			this->diagonal_counter[counter_index] = other.diagonal_counter[counter_index];
		}
		this->row_counter[2] = other.row_counter[2];
		this->col_counter[2] = other.col_counter[2];

		this->nr_of_available_moves = other.nr_of_available_moves;
	}
}
/*
TicTacToe::Board::Board() : coordinates({ UNOCCUPIED }), row_counter({ EMPTY }), col_counter({ EMPTY }), diagonal_counter({ EMPTY }), nr_of_available_moves(9) {};

TicTacToe::Board::Board(int coordinates[3][3], int rows_counters[3], int cols_counters[3], int diagonals_counters[2], int nr_of_available_moves) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			this->coordinates[col][row] = coordinates[col][row];
		}
	}

	for (int counter_index = 0; counter_index < 2; counter_index++) {
		this->row_counter[counter_index] = rows_counters[counter_index];
		this->col_counter[counter_index] = cols_counters[counter_index];
		this->diagonal_counter[counter_index] = diagonals_counters[counter_index];
	}
	this->row_counter[2] = rows_counters[2];
	this->col_counter[2] = cols_counters[2];

	this->nr_of_available_moves = nr_of_available_moves;
}

void TicTacToe::Board::CopyBoard(Board other) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			this->coordinates[col][row] = other.coordinates[col][row];
		}
	}

	for (int counter_index = 0; counter_index < 2; counter_index++) {
		this->row_counter[counter_index] = other.row_counter[counter_index];
		this->col_counter[counter_index] = other.col_counter[counter_index];
		this->diagonal_counter[counter_index] = other.diagonal_counter[counter_index];
	}
	this->row_counter[2] = other.row_counter[2];
	this->col_counter[2] = other.col_counter[2];

	this->nr_of_available_moves = other.nr_of_available_moves;
}*/;