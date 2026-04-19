#pragma once

#include "Game.h"

template <unsigned int x, unsigned int y>
struct Game::Board : public Printable {
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
};