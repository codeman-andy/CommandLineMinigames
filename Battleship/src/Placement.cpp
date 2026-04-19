#include "Battleship.h"

struct Battleship::Placement {
	int x_start;
	int x_end;
	int y_start;
	int y_end;

	Placement() : x_start(0), x_end(0), y_start(0), y_end(0) {}

	Placement(int x_start, int x_end, int y_start, int y_end)
		: x_start(x_start), x_end(x_end), y_start(y_start), y_end(y_end)
	{}

	void Sort()
	{
		int sorted[4];
		sorted[0] = (this->x_end >= this->x_start) ? this->x_start : this->x_end;
		sorted[1] = (sorted[0] == this->x_start) ? this->x_end : this->x_start;
		sorted[2] = (this->y_end >= this->y_start) ? this->y_start : this->y_end;
		sorted[3] = (sorted[2] == this->y_start) ? this->y_end : this->y_start;

		this->x_start = sorted[0];
		this->x_end = sorted[1];
		this->y_start = sorted[2];
		this->y_end = sorted[3];
	}

	bool isValid(const int& vessel_size) const
	{
		if ((this->x_start % 1 != 0 && this->x_start < 0 && this->x_start > 10) &&
			(this->x_end % 1 != 0 && this->x_end < 0 && this->x_end > 10) &&
			(this->y_start % 1 != 0 && this->y_start < 0 && this->y_start > 8) &&
			(this->y_end % 1 != 0 && this->y_end < 0 && this->y_end > 8))
		{
			Log("\nYou tried to place outside the board. Please, type your coordinates again.\n\n");
			return INVALID_PLACEMENT;
		}

		else if ((this->x_end - this->x_start) + (this->y_end - this->y_start) != (vessel_size - 1))
		{
			Log("\nYour placement did not respect the vessel's size. Please, type your coordinates again.\n\n");
			return INVALID_PLACEMENT;
		}

		else return VALID;
	}
};