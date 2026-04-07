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

	bool isFull() const {
		int letter_count = 0;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; (j < 3) && (board.coordinates[j][i] != UNOCCUPIED); j++) letter_count++;
		}

		return (letter_count == 9);
	}

	move* GetValidMoves() const {
		move* valid_moves = (move*) new move[nr_of_available_moves];

		int index = 0;
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				if (coordinates[row][col] == UNOCCUPIED) {
					valid_moves[index] = move(col, row);
					index++;
				}
			}
		}

		return valid_moves;
	}

	int CheckState(const move& last_move) {
		if (board.row_counter[last_move.y] == FULL && CheckForWinner(board, last_move.y, CheckForRow) == WINNER_FOUND) return WINNER_FOUND;
		if (board.col_counter[last_move.x] == FULL && CheckForWinner(board, last_move.x, CheckForCol) == WINNER_FOUND) return WINNER_FOUND;

		if (board.diagonal_counter[0] == FULL && CheckForWinner(board, 0, CheckForDiagLeft) == WINNER_FOUND) return WINNER_FOUND;
		if (board.diagonal_counter[1] == FULL && CheckForWinner(board, 1, CheckForDiagRight) == WINNER_FOUND) return WINNER_FOUND;

		return RUNNING;
	}

	void Reset() {
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				this->coordinates[col][row] = UNOCCUPIED;
			}
		}

		for (int counter_index = 0; counter_index < 2; counter_index++) {
			this->row_counter[counter_index] = EMPTY;
			this->col_counter[counter_index] = EMPTY;
			this->diagonal_counter[counter_index] = EMPTY;
		}
		this->row_counter[2] = EMPTY;
		this->col_counter[2] = EMPTY;

		this->nr_of_available_moves = 9;
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
};