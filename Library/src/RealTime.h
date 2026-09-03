#pragma once

#include "Move.h"

#include "Game/Settings.h"

#include "IRealTime.h"

template <unsigned int x, unsigned int y>
struct RealTime : public IRealTime {
	int coordinates[x][y];
	Move LastMove;

	RealTime() : coordinates({ UNOCCUPIED }), LastMove(Move(1, 0))
	{
	};

	RealTime(const RealTime& other)
	{
		memcpy(this->coordinates, other.coordinates, sizeof(other.coordinates));
	}

	virtual void Reset() override
	{
		for (int col = 0; col < x; col++)
		{
			for (int row = 0; row < y; row++)
			{
				this->coordinates[col][row] = UNOCCUPIED;
			}
		}
	}

	virtual State OnUpdate() override = 0;

	void SetNextMove(const Move& move) override
	{
		if (IsValid(move))
			LastMove = move;
	}

	bool IsValid(const Move& move) const override
	{
		return (move.x * LastMove.x + move.y * LastMove.y == 0);
	}

	virtual bool OutOfBounds() const = 0;
};