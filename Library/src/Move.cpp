#include "Move.h"

move::move() : x(0), y(0) {}

move::move(const int& X, const int& Y) : x(X), y(Y) {}

bool move::operator==(const move& other)
{
	return (this->x == other.x && this->y == other.y);
}

bool move::operator!=(const move& other)
{
	return (this->x != other.x || this->y != other.y);
}