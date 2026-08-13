#pragma once

#include "IBoard.h"

#include "Utils/Log.h"

#include "Game/Settings.h"


template <unsigned int x, unsigned int y>
struct Gameboard : public IBoard {
	int coordinates[x][y];

	Gameboard() : coordinates({ UNOCCUPIED }) {};

	Gameboard(const Gameboard& other)
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

	bool isPossible(const Move& Move) const
	{
		if (this->coordinates[Move.x][Move.y] == UNOCCUPIED) return VALID;

		else Log("The coordinate you picked is already occupied. Please, choose another.\n");
		return INVALID_MOVE;
	}

	bool XisValid(const int& Coord) const
	{
		if (Coord % 1 == 0 && Coord >= 0 && Coord <= x) return VALID;

		else Log("Your last coordinate was invalid. Please, type your coordinates again.\n");
		return INVALID_COORDINATE;
	}

	bool YisValid(const int& Coord) const
	{
		if (Coord % 1 == 0 && Coord >= 0 && Coord <= y) return VALID;

		else Log("Your last coordinate was invalid. Please, type your coordinates again.\n");
		return INVALID_COORDINATE;
	}

	virtual void OnUpdate()
	{
		// Lorem Ipsum
	}

	virtual ~Gameboard() {}
};