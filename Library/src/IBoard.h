#pragma once

#include "IPrintable.h"


class IBoard : public IPrintable {
public:
	virtual void OnUpdate() = 0;

	virtual void Reset() = 0;
};