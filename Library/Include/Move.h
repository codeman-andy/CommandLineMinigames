#pragma once


/*
 * A simple struct which stores a single TicTacToe move.
 */

struct move {
	/* Variables */
	int x;
	int y;

	/* Constructors */
	move();
	move(const int& X, const int& Y);

	/* Operator-Overloads */
	bool operator==(const move& other);
	bool operator!=(const move& other);
};