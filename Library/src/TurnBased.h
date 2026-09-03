#pragma once

#include "Move.h"

#include "Game/Settings.h"

#include "ITurnBased.h"

template <unsigned int x, unsigned int y>
struct TurnBased : public ITurnBased {
	int coordinates[x][y];

	TurnBased() : coordinates({ UNOCCUPIED })
	{
	};

	TurnBased(const TurnBased& other)
	{
		memcpy(this->coordinates, other.coordinates, sizeof(other.coordinates));
	}

	virtual void Reset() override
	{
		memset(this->coordinates, UNOCCUPIED, sizeof(this->coordinates));
	}

	virtual State CheckState(const Move& last_move) const override
	{
		return RUNNING;
	}

	virtual  bool IsEmpty() const override
	{
		return RUNNING;
	}

	virtual  bool IsFull()  const override
	{
		return RUNNING;
	}

	bool IsPossible(const Move& Move) const override
	{
		if (this->coordinates[Move.x][Move.y] == UNOCCUPIED) return VALID;

		else Log("The coordinate you picked is already occupied. Please, choose another.\n");
		return INVALID_MOVE;
	}

	bool XisValid(const int& Coord) const override
	{
		if (Coord % 1 == 0 && Coord >= 0 && Coord <= x) return VALID;

		else Log("Your last coordinate was invalid. Please, type your coordinates again.\n");
		return INVALID_COORDINATE;
	}

	bool YisValid(const int& Coord) const override
	{
		if (Coord % 1 == 0 && Coord >= 0 && Coord <= y) return VALID;

		else Log("Your last coordinate was invalid. Please, type your coordinates again.\n");
		return INVALID_COORDINATE;
	}

	bool IsValid(const Move& move) const override
	{
		return (XisValid(move.x) && YisValid(move.y));
	}

	virtual ~TurnBased() {}
};