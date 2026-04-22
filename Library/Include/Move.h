#pragma once


/*
 * A simple struct which stores a single TicTacToe Move.
 */

struct Move {
	/* Variables */
	int x;
	int y;

	/* Constructors */
	Move();
	Move(const int& X, const int& Y);

	/* Operator-Overloads */
	bool operator==(const Move& other);
	bool operator!=(const Move& other);
};