#pragma once

#include "Game.h"

template <unsigned int x, unsigned int y>
struct Game::Board : public IPrintable {
	inline static const char CharTranslation[3] = { '-', 'X', 'O' };
	int coordinates[x][y];

	Board() : coordinates({ UNOCCUPIED }) {};

	Board(const Board& other)
	{
		memcpy(this->coordinates, other.coordinates, sizeof(other.coordinates));
	}

	virtual void Reset()
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

	virtual ~Board() {}
};