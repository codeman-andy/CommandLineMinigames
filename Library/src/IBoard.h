#pragma once

#include "IPrintable.h"

#include "Move.h"

#include "Game/Settings.h"

class IBoard : public IPrintable {
public:
	virtual State OnUpdate() = 0;

	virtual  void SetNextMove(const Move& move) = 0;

	virtual  void Reset() = 0;
};