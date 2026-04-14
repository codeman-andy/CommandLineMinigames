#include "Vessel.cpp"

struct Battleship::Board::Home : public Battleship::Board {
	int nr_of_vessels;
	Vessel vessels[5];
	Placement placements[5];

	Home() : Board(), nr_of_vessels(5), placements()
	{
		vessels[CARRIER] = Vessel::Carrier();
		vessels[BATTLESHIP] = Vessel::Battleship();
		vessels[DESTROYER] = Vessel::Destroyer();
		vessels[SUBMARINE] = Vessel::Submarine();
		vessels[PATROL_BOAT] = Vessel::PatrolBoat();
	}

	Home(const Board::Home& other) : nr_of_vessels(other.nr_of_vessels)
	{
		memcpy(this->coordinates, other.coordinates, sizeof(other.coordinates));
		memcpy(this->vessels, other.vessels, sizeof(other.vessels));
		memcpy(this->placements, other.placements, sizeof(other.placements));
	}

	bool isEmpty() const
	{
		return (this->nr_of_vessels == 0);
	}

	bool isFull() const
	{
		return (this->nr_of_vessels == 5);
	}

	void PlaceHorizontally(const int& x_start, const int& x_end, const int& y)
	{
		for (int x = x_start; x <= x_end; x++)
		{
			this->coordinates[x][y] = X;
		}
	}

	void PlaceVertically(const int& x, const int& y_start, const int& y_end)
	{
		for (int y = y_start; y <= y_end; y++)
		{
			this->coordinates[x][y] = X;
		}
	}

	void PlaceVessel(const int& vessel_type, const Placement& placement)
	{
		this->placements[vessel_type] = placement;

		if (placement.x_start == placement.x_end) PlaceVertically(placement.x_start, placement.y_start, placement.y_end);

		else PlaceHorizontally(placement.x_start, placement.x_end, placement.y_start);
	}

	int IdentifyVessel(const int& x, const int& y) const
	{
		int v_type = 0;
		while ((x < this->placements[v_type].x_start || x > this->placements[v_type].x_end)
			|| (y < this->placements[v_type].y_start || y > this->placements[v_type].y_end))
		{
			v_type++;
		}
		return v_type;
	}

	void MarkHit(const int& x, const int& y) override
	{
		int v_type = IdentifyVessel(x, y);

		this->vessels[v_type].Hit();

		this->coordinates[x][y] = O;

		if (this->vessels[v_type].hit_points == 0)
		{
			std::cout << "The " << Vessel::Name[v_type] << " has been destroyed!\n";

			this->nr_of_vessels--;

			if (this->nr_of_vessels == 0) STATE = FINISHED;
		}
	}

	int CheckHit(const int& x, const int& y) const
	{
		if (this->coordinates[x][y] == UNOCCUPIED)
		{
			Log("Miss!\n");
			return MISS;
		}

		else
		{
			Log("You have hit a ship!\n");
			return HIT;
		}
	}

	void Reset() override
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

		this->nr_of_vessels = 5;
	}
};



struct Battleship::Board::Moves : Battleship::Board {

	void MarkHit(const int& x, const int& y) override
	{
		this->coordinates[x][y] = O;
	}

	void Reset() override
	{
		for (int x = 0; x < 11; x++)
		{
			for (int y = 0; y < 9; y++)
			{
				this->coordinates[x][y] = UNOCCUPIED;
			}
		}
	}
};