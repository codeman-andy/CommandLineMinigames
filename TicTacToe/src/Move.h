#pragma once

struct move {
	int x;
	int y;

	move();

	move(const int& X, const int& Y);

	bool operator==(const move& other);

	bool operator!=(const move& other);
};