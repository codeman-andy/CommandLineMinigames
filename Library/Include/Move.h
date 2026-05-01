#pragma once


/*
 * A simple struct which stores a single TicTacToe Move.
 */

struct Move {
	/* Variables */
	int x, y;

	/* Constructors */
	Move() : x(0), y(0) {}
	Move(const int& X, const int& Y) : x(X), y(Y) {}

	/* Operator-Overloads */
	bool operator==(const Move& other)
	{
		return (this->x == other.x && this->y == other.y);
	}

	bool operator!=(const Move& other)
	{
		return (this->x != other.x || this->y != other.y);
	}
};