#include "Battleship.h"

#include "Vessel.cpp"

struct Battleship::Board {
	inline static const char const CharTranslation[3] = { '-', 'X', 'O' };
	int coordinates[9][11];
	int nr_of_vessels;
	Vessel vessels[5];

	Board() : coordinates({ UNOCCUPIED }), nr_of_vessels(0), vessels() {}

	Board(const Board& other) : nr_of_vessels(0)
	{
		memcpy(this->coordinates, other.coordinates, sizeof(other.coordinates));
	}

	move* GetValidMoves() const
	{
		move* valid_moves = (move*) new move[nr_of_available_moves];

		int index = 0;
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 11; col++)
			{
				if (coordinates[row][col] == UNOCCUPIED)
				{
					valid_moves[index] = move(col, row);
					index++;
				}
			}
		}

		return valid_moves;
	}

	bool isEmpty() const
	{
		return (nr_of_available_moves == 99);
	}

	bool isFull() const
	{
		return (nr_of_available_moves == 0);
	}

	void PlaceHorizontally(const int& x_start, const int& x_end, const int& y)
	{
		for (int i = x_start; i <= x_end; i++)
		{
			coordinates[y][i] = X;
		}
	}

	void PlaceVertically(const int& x, const int& y_start, const int& y_end)
	{
		for (int i = y_start; i <= y_end; i++)
		{
			coordinates[i][x] = X;
		}
	}

	int PlaceVessel(const vessel_type& vessel, const int& x_start, const int& x_end, const int& y_start, const int& y_end)
	{
		switch (vessel)
		{
		case CARRIER:
			Vessel boat = Vessel::Carrier();
			vessels[vessel] = boat;
		case BATTLESHIP:
			Vessel boat = Vessel::Battleship();
			vessels[vessel] = boat;
		case DESTROYER:
			Vessel boat = Vessel::Destroyer();
			vessels[vessel] = boat;
		case SUBMARINE:
			Vessel boat = Vessel::Submarine();
			vessels[vessel] = boat;
		case PATROL_BOAT:
			Vessel boat = Vessel::PatrolBoat();
			vessels[vessel] = boat;
		}

		if (x_start == x_end) PlaceVertically(x_start, y_start, y_end);

		else PlaceHorizontally(x_start, x_end, y_start);
	}

	void MarkHit(const int& x, const int& y)
	{
		coordinates[y][x] = O;
	}

	int CheckState()
	{
		return 1;
	}

	void Reset()
	{
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 11; col++)
			{
				this->coordinates[row][col] = UNOCCUPIED;
			}
		}

		for (int counter_index = 0; counter_index < 9; counter_index++)
		{
			this->row_counter[counter_index] = EMPTY;
			this->col_counter[counter_index] = EMPTY;
		}
		this->col_counter[9] = EMPTY;
		this->col_counter[10] = EMPTY;

		this->nr_of_available_moves = 99;
	}

	void Print()
	{
		Log("  0 1 2\n");
		Log("  -----\n");

		for (int i = 0; i < 3; i++)
		{
			std::cout << i << "|" << CharTranslation[coordinates[i][0]] << " " << CharTranslation[coordinates[i][1]] << " " << CharTranslation[coordinates[i][2]] << "|" << std::endl;
		}

		Log("  -----\n");
	}
};