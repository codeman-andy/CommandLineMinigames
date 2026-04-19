#include "Placement.cpp"
#include "Vessel.cpp"

struct Battleship::Homeboard : public Game::Board<11,9> {
	int nr_of_vessels;
	Vessel vessels[5];
	Placement placements[5];

	Homeboard() : nr_of_vessels(5), placements()
	{
		vessels[CARRIER] = Vessel::Carrier();
		vessels[BATTLESHIP] = Vessel::Battleship();
		vessels[DESTROYER] = Vessel::Destroyer();
		vessels[SUBMARINE] = Vessel::Submarine();
		vessels[PATROL_BOAT] = Vessel::PatrolBoat();
	}

	Homeboard(const Homeboard& other) : nr_of_vessels(other.nr_of_vessels)
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

	void PlaceVessel(const vessel_type& vessel_type, const Placement& placement)
	{
		this->placements[vessel_type] = placement;

		if (placement.x_start == placement.x_end) PlaceVertically(placement.x_start, placement.y_start, placement.y_end);

		else PlaceHorizontally(placement.x_start, placement.x_end, placement.y_start);
	}

	vessel_type IdentifyVessel(const int& x, const int& y) const
	{
		int type = 0;
		while ((x < this->placements[type].x_start || x > this->placements[type].x_end)
			|| (y < this->placements[type].y_start || y > this->placements[type].y_end))
		{
			type++;
		}
		return static_cast<vessel_type>(type);
	}

	void MarkHit(const int& x, const int& y)
	{
		this->coordinates[x][y] = O;

		vessel_type type = IdentifyVessel(x, y);

		this->vessels[type].Hit();

		if (this->vessels[type].hit_points == 0)
		{
			std::cout << "The " << Vessel::Name[type] << " has been destroyed!\n";

			this->nr_of_vessels--;

			if (this->nr_of_vessels == 0) STATE = FINISHED;
		}
	}

	void MarkMiss(const int& x, const int& y)
	{
		this->coordinates[x][y] = X;
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

	void Print() const override
	{
		Log("   0 1 2 3 4 5 6 7 8 9 10\n");
		Log("   ---------------------\n");

		for (int y = 8; y >= 0; y--)
		{
			std::cout << y << "| ";
			for (int x = 0; x < 11; x++)
			{
				std::cout << CharTranslation[this->coordinates[x][y]] << " ";
			}
			std::cout << "|" << std::endl;
		}

		Log("   ---------------------\n");
	}
};



struct Battleship::Hitsboard : Game::Board<11,9> {

	void MarkHit(const int& x, const int& y)
	{
		this->coordinates[x][y] = O;
	}

	void MarkMiss(const int& x, const int& y)
	{
		this->coordinates[x][y] = X;
	}

	void Print() const override
	{
		Log("   0 1 2 3 4 5 6 7 8 9 10\n");
		Log("   ---------------------\n");

		for (int y = 8; y >= 0; y--)
		{
			std::cout << y << "| ";
			for (int x = 0; x < 11; x++)
			{
				std::cout << CharTranslation[this->coordinates[x][y]] << " ";
			}
			std::cout << "|" << std::endl;
		}

		Log("   ---------------------\n");
	}
};