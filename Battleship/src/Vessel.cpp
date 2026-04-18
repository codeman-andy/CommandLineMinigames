#include "Battleship.h"

struct Battleship::Vessel {
	inline static const char* const Name[5] = { "Carrier", "Battleship", "Destroyer", "Submarine", "Patrol Boat" };
	inline static const int Size[5] = { 5, 4, 3, 3, 2 };
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

	static const char* GetVesselName(const vessel_type& type)
	{
		return Name[type];
	}

	static const int GetVesselSize(const vessel_type& type)
	{
		return Size[type];
	}

	void Hit()
	{
		this->hit_points--;
	}

	void Reset()
	{
		this->hit_points = this->size;
	}
};