#include "Move.h"

int x;
int y;

move::move() : x(0), y(0) {};

move::move(const int& X, const int& Y) : x(X), y(Y) {};

bool move::operator==(const move& other) {
	return (x == other.x && y == other.y);
}

bool move::operator!=(const move& other) {
	return (x != other.x || y != other.y);
}