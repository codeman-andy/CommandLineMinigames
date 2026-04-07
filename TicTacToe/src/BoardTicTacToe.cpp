#include "Printable.h"
#include "TicTacToe.h"

struct TicTacToe::Board : Printable {
	inline static const char const CharTranslation[3] = { '-', 'X', 'O' };
	int coordinates[3][3];
	int row_counter[3];
	int col_counter[3];
	int diagonal_counter[2];
	int nr_of_available_moves;

	Board() : coordinates({ UNOCCUPIED }), row_counter({ EMPTY }), col_counter({ EMPTY }), diagonal_counter({ EMPTY }), nr_of_available_moves(9)
	{
	}

	Board(const Board& other) : nr_of_available_moves(other.nr_of_available_moves) {
		memcpy(this->coordinates, other.coordinates, sizeof(other.coordinates));
		memcpy(this->row_counter, other.row_counter, sizeof(other.row_counter));
		memcpy(this->col_counter, other.col_counter, sizeof(other.col_counter));
		memcpy(this->diagonal_counter, other.diagonal_counter, sizeof(other.diagonal_counter));
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

	bool isFull() const {
		return (nr_of_available_moves == 0);
	}

	int CheckForWinner(const int& index, const int& CheckFor) const {
		switch (CheckFor) {
		case CheckForRow:
			if (coordinates[index][0] == coordinates[index][1] && coordinates[index][0] == coordinates[index][2]) return WINNER_FOUND;
			[[fallthrough]];
		case CheckForCol:
			if (coordinates[0][index] == coordinates[1][index] && coordinates[0][index] == coordinates[2][index]) return WINNER_FOUND;
			[[fallthrough]];
		case CheckForDiagLeft:
			if (coordinates[0][0] == coordinates[1][1] && coordinates[0][0] == coordinates[2][2]) return WINNER_FOUND;
			[[fallthrough]];
		case CheckForDiagRight:
			if (coordinates[0][2] == coordinates[1][1] && coordinates[0][2] == coordinates[2][0]) return WINNER_FOUND;
		}

		return RUNNING;
	}

	int CheckState(const move& last_move) const {
		if (row_counter[last_move.y] == FULL && CheckForWinner(last_move.y, CheckForRow) == WINNER_FOUND) return WINNER_FOUND;
		if (col_counter[last_move.x] == FULL && CheckForWinner(last_move.x, CheckForCol) == WINNER_FOUND) return WINNER_FOUND;

		if (diagonal_counter[0] == FULL && CheckForWinner(0, CheckForDiagLeft) == WINNER_FOUND) return WINNER_FOUND;
		if (diagonal_counter[1] == FULL && CheckForWinner(1, CheckForDiagRight) == WINNER_FOUND) return WINNER_FOUND;

		if (isFull()) return DRAW;

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

	void Print() {
		Log("  0 1 2\n");
		Log("  -----\n");

		for (int i = 0; i < 3; i++) {
			std::cout << i << "|" << CharTranslation[coordinates[i][0]] << " " << CharTranslation[coordinates[i][1]] << " " << CharTranslation[coordinates[i][2]] << "|" << std::endl;
		}

		Log("  -----\n");
	}
};