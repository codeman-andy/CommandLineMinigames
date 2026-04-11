#include "Battleship.h"

#include "Vessel.cpp"

struct Battleship::Board {
	inline static const char CharTranslation[3] = { '-', 'X', 'O' };
	int coordinates[11][9];
	int nr_of_vessels;
	Vessel vessels[5];
	Placement placements[5];

	Board() : coordinates({ UNOCCUPIED }), nr_of_vessels(0), vessels(), placements({ 0 }) {}

	Board(const Board& other) : nr_of_vessels(0)
	{
		memcpy(this->coordinates, other.coordinates, sizeof(other.coordinates));
		memcpy(this->placements, other.placements, sizeof(other.placements));
	}

	/* TO BE REFACTORED
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
	*/

	bool isEmpty() const
	{
		return (nr_of_vessels == 0);
	}

	bool isFull() const
	{
		return (nr_of_vessels == 5);
	}

	void PlaceHorizontally(const int& x_start, const int& x_end, const int& y)
	{
		for (int i = x_start; i <= x_end; i++)
		{
			coordinates[i][y] = X;
		}
	}

	void PlaceVertically(const int& x, const int& y_start, const int& y_end)
	{
		for (int i = y_start; i <= y_end; i++)
		{
			coordinates[x][i] = X;
		}
	}

	void PlaceVessel(const int& vessel, const Placement& placement)
	{
		switch (vessel)
		{
		case CARRIER:
			vessels[vessel] = Vessel::Carrier();
			break;
		case BATTLESHIP:
			vessels[vessel] = Vessel::Battleship();
			break;
		case DESTROYER:
			vessels[vessel] = Vessel::Destroyer();
			break;
		case SUBMARINE:
			vessels[vessel] = Vessel::Submarine();
			break;
		case PATROL_BOAT:
			vessels[vessel] = Vessel::PatrolBoat();
			break;
		}

		placements[vessel] = placement;

		if (placement.x_start == placement.x_end) PlaceVertically(placement.x_start, placement.y_start, placement.y_end);

		else PlaceHorizontally(placement.x_start, placement.x_end, placement.y_start);

		nr_of_vessels++;
	}

	int IdentifyVessel(const int& x, const int& y) const
	{
		int v_type = 0;
		while ((x != this->placements[v_type].x_start && x != this->placements[v_type].x_end)
			|| (y != this->placements[v_type].y_start && y != this->placements[v_type].y_end))
		{
			v_type++;
		}
		return v_type;
	}

	void MarkHit(const int& x, const int& y)
	{
		int v_type = IdentifyVessel(x, y);
		this->vessels[v_type].Hit();

		this->coordinates[x][y] = O;

		Log("You have hit a ship!\n");
	}

	int CheckHit(const int& x, const int& y)
	{
		if (this->coordinates[x][y] == UNOCCUPIED)
		{
			Log("Miss!\n");
			return MISS;
		}

		MarkHit(x, y);

		return HIT;
	}

	int CheckState()
	{
		return 1;
	}

	void Reset()
	{
		for (int x = 0; x < 11; x++)
		{
			for (int y = 0; y < 9; y++)
			{
				this->coordinates[x][y] = UNOCCUPIED;
			}
		}

		for (int i = 0; i < 5; i++)
		{
			this->vessels[i].Reset();
		}

		this->nr_of_vessels = 0;
	}

	void Print() const
	{
		Log("  A B C D E F G H I J K\n");
		Log("  ---------------------\n");

		for (int y = 9; y > 0; y--)
		{
			std::cout << y << "|";
			for (int x = 0; x < 11; x++)
			{
				std::cout << this->CharTranslation[this->coordinates[x][y]];
			}
			std::cout << "|" << std::endl;
		}

		Log("  ---------------------\n");
	}
};