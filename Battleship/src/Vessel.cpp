#include "Battleship.h"

struct Battleship::Vessel {
	inline static const char* const vessel_names[5] = { "Carrier", "Battleship", "Destroyer", "Submarine", "Patrol Boat" };
	vessel_type type;
	int size;
	int hit_points;

	Vessel() : type(BATTLESHIP), size(32), hit_points(32) {}

	Vessel(vessel_type type, int size) : type(type), size(size), hit_points(size) {}

	static Vessel PatrolBoat()
	{
		return Vessel(PATROL_BOAT, 2);
	}

	static Vessel Submarine()
	{
		return Vessel(SUBMARINE, 3);
	}

	static Vessel Destroyer()
	{
		return Vessel(DESTROYER, 3);
	}

	static Vessel Battleship()
	{
		return Vessel(BATTLESHIP, 4);
	}

	static Vessel Carrier()
	{
		return Vessel(CARRIER, 5);
	}

	void Hit() {
		this->hit_points--;

		if (hit_points == 0)
		{
			std::cout << "The " << vessel_names[this->type] << " has been destroyed!\n";
		}
	}

	void Reset()
	{
		this->hit_points = this->size;
	}
};