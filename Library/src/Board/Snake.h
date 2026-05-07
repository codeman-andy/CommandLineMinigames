#pragma once

#include "Board.h"


/* Specialized Snake Game Board */
template <unsigned int x, unsigned int y>
struct Board : public Gameboard<x, y> {
	int x_Head, y_Head, x_Tail, y_Tail;

	struct SnakeCell {
		int x, y;
		SnakeCell* next, ahead;
	};

	Board()
	{}

	Board(const Board& other)
	{
		memcpy(this->coordinates, other.coordinates, sizeof(other.coordinates));
	}

	Move* GetValidMoves() const
	{}

	bool isEmpty() const
	{}

	bool isFull() const
	{}

	int hasWinner(const int& index, const int& Check) const
	{}

	State CheckState(const Move& last_move) const
	{
		if (1) return FINISHED;

		else return RUNNING;
	}

	void Mark(const int& x, const int& y)
	{
		this->coordinates[x][y] = X;
	}

	void OnUpdate() override
	{

	}

	void PrintFrame() const
	{
		Log("  ");

		for (int i = 0; i < x; i++)
			Log("-");

		Log("\n");
	}

	void Print() const override
	{
		PrintFrame();

		for (int y = this->y; y >= 0; y--)
		{
			std::cout << "| ";
			for (int x = 0; x < this->x; x++)
			{
				std::cout << CharTranslation[this->coordinates[x][y]];
			}
			std::cout << "|" << std::endl;
		}

		PrintFrame();
	}

	~Board()
	{}
};