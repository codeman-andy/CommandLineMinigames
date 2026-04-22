#include "Move.h"

Move::Move() : x(0), y(0) {}

Move::Move(const int& X, const int& Y) : x(X), y(Y) {}

bool Move::operator==(const Move& other)
{
	return (this->x == other.x && this->y == other.y);
}

bool Move::operator!=(const Move& other)
{
	return (this->x != other.x || this->y != other.y);
}