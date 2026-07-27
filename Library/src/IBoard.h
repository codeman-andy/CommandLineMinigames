#pragma once

#include "IPrintable.h"

#include "Move.h"

class IBoard : public IPrintable {
public:
	virtual void OnUpdate() = 0;

	virtual void SetNextMove(const Move& move) = 0;

	virtual void Reset() = 0;
};