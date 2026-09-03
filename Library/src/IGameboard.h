#pragma once

#include "IPrintable.h"

#include "Move.h"

#include "Game/Settings.h"

class IGameboard : public IPrintable {
public:
	virtual  void Reset() = 0;
};