#pragma once

#include "Move.h"

#include "Game/Settings.h"

#include "IGameboard.h"

class IRealTime : public IGameboard {
public:
	virtual State OnUpdate() = 0;

	virtual void SetNextMove(const Move& move) = 0;

	virtual bool IsValid(const Move& move) const = 0;

	virtual bool OutOfBounds() const = 0;
};