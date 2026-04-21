#include "TicTacToe.h"

struct TicTacToe::Board : public Game::Board<3,3> {
	int row_counter[3];
	int col_counter[3];
	int diagonal_counter[2];
	int nr_of_available_moves;

	Board() : row_counter({ EMPTY }), col_counter({ EMPTY }), diagonal_counter({ EMPTY }), nr_of_available_moves(9) {}

	Board(const Board& other) : nr_of_available_moves(other.nr_of_available_moves)
	{
		memcpy(this->coordinates, other.coordinates, sizeof(other.coordinates));
		memcpy(this->row_counter, other.row_counter, sizeof(other.row_counter));
		memcpy(this->col_counter, other.col_counter, sizeof(other.col_counter));
		memcpy(this->diagonal_counter, other.diagonal_counter, sizeof(other.diagonal_counter));
	}

	move* GetValidMoves() const
	{
		move* valid_moves = (move*) new move[this->nr_of_available_moves];

		int index = 0;
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				if (this->coordinates[x][y] == UNOCCUPIED)
				{
					valid_moves[index] = move(x, y);
					index++;
				}
			}
		}

		return valid_moves;
	}

	bool isEmpty() const
	{
		return (this->nr_of_available_moves == 9);
	}

	bool isFull() const
	{
		return (this->nr_of_available_moves == 0);
	}

	int hasWinner(const int& index, const int& Check) const
	{
		switch (Check)
		{
		case InRow:
			if (coordinates[0][index] == coordinates[1][index] && coordinates[0][index] == coordinates[2][index]) return GAME_END;
			else break;
		case InCol:
			if (coordinates[index][0] == coordinates[index][1] && coordinates[index][0] == coordinates[index][2]) return GAME_END;
			else break;
		case InDiagLeft:
			if (coordinates[0][0] == coordinates[1][1] && coordinates[0][0] == coordinates[2][2]) return GAME_END;
			else break;
		case InDiagRight:
			if (coordinates[0][2] == coordinates[1][1] && coordinates[0][2] == coordinates[2][0]) return GAME_END;
			else break;
		}

		return RUNNING;
	}

	state CheckState(const move& last_move) const
	{
		if ( (this->row_counter[last_move.y] == FULL && this->hasWinner(last_move.y, InRow))
		  || (this->col_counter[last_move.x] == FULL && this->hasWinner(last_move.x, InCol))
		  || (this->diagonal_counter[0] == FULL && this->hasWinner(0, InDiagLeft))
		  || (this->diagonal_counter[1] == FULL && this->hasWinner(1, InDiagRight))
		   ) return FINISHED;

		else if (this->isFull()) return DRAW;

		else return RUNNING;
	}

	void Mark(const int& x, const int& y, const letter& letter)
	{
		this->coordinates[x][y] = letter;

		this->row_counter[y] += 1;
		this->col_counter[x] += 1;

		if (x == y) this->diagonal_counter[0]++;

		if (x + y == 2) this->diagonal_counter[1]++;

		this->nr_of_available_moves--;
	}

	void Reset() override
	{
		for (int row = 0; row < 3; row++)
		{
			for (int col = 0; col < 3; col++)
			{
				this->coordinates[row][col] = UNOCCUPIED;
			}
		}

		for (int counter_index = 0; counter_index < 2; counter_index++)
		{
			this->row_counter[counter_index] = EMPTY;
			this->col_counter[counter_index] = EMPTY;
			this->diagonal_counter[counter_index] = EMPTY;
		}
		this->row_counter[2] = EMPTY;
		this->col_counter[2] = EMPTY;

		this->nr_of_available_moves = 9;
	}

	void Print() const override
	{
		Log("  0 1 2\n");
		Log("  -----\n");

		for (int y = 0; y < 3; y++)
		{
			std::cout << y << "|" << CharTranslation[coordinates[0][y]] << " " << CharTranslation[coordinates[1][y]] << " " << CharTranslation[coordinates[2][y]] << "|" << std::endl;
		}

		Log("  -----\n");
	}

	~Board() {}
};