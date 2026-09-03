#pragma once

#include "IGameboard.h"

#include "Utils/Log.h"

#include "Game/Settings.h"


template <unsigned int x, unsigned int y>
struct Gameboard : public IGameboard {
	int coordinates[x][y];

	Gameboard() : coordinates({ UNOCCUPIED })
	{
	};

	Gameboard(const Gameboard& other)
	{
		memcpy(this->coordinates, other.coordinates, sizeof(other.coordinates));
	}

	void Reset() override
	{
		memset(this->coordinates, UNOCCUPIED, sizeof(this->coordinates));
	}

	virtual ~Gameboard() {}
};