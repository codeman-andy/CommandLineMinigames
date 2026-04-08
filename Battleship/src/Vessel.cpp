#include "Battleship.h"

struct Battleship::Vessel {
	inline static const char* const vessel_names[5] = { "Carrier", "Battleship", "Destroyer", "Submarine", "Patrol Boat" };
	vessel_type type;
	int size;
	int x_start, x_end;
	int y_start, y_end;
	int hit_points;

	Vessel() : type(Battle_Ship), size(0), x_start(0), x_end(0), y_start(0), y_end(0), hit_points(100) {}

	Vessel(vessel_type type, int size, int x_start, int x_end, int y_start, int y_end) : type(type), size(size), x_start(x_start), x_end(x_end), y_start(y_start), y_end(y_end), hit_points(size) {}

	static Vessel CreatePatrolBoat(int x_start, int x_end, int y_start, int y_end)
	{
		return Vessel(Patrol_Boat, 2, x_start, x_end, y_start, y_end);
	}

	static Vessel CreateSubmarine(int x_start, int x_end, int y_start, int y_end)
	{
		return Vessel(Submarine, 3, x_start, x_end, y_start, y_end);
	}

	static Vessel CreateDestroyer(int x_start, int x_end, int y_start, int y_end)
	{
		return Vessel(Destroyer, 3, x_start, x_end, y_start, y_end);
	}

	static Vessel CreateBattleship(int x_start, int x_end, int y_start, int y_end)
	{
		return Vessel(Battle_Ship, 4, x_start, x_end, y_start, y_end);
	}

	static Vessel CreateCarrier(int x_start, int x_end, int y_start, int y_end)
	{
		return Vessel(Carrier, 5, x_start, x_end, y_start, y_end);
	}
};