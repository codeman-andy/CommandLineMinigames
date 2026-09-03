#pragma once

#include "Move.h"

#include "Game/Settings.h"

#include "IGameboard.h"

class ITurnBased : public IGameboard {
public:
	virtual State CheckState(const Move& last_move) const = 0;

	virtual  bool IsEmpty() const = 0;

	virtual  bool IsFull()  const = 0;

	virtual  bool IsPossible(const Move& Move) const = 0;

	virtual  bool XisValid(const int& Coord)   const = 0;

	virtual  bool YisValid(const int& Coord)   const = 0;

	virtual  bool IsValid(const Move& move)    const = 0;
};