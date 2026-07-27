#pragma once

// Imports the Board-abstract-struct
#include "Board.h"


/* Specialized Snake Game Board */
template <unsigned int x, unsigned int y>
struct Board : public Gameboard<x, y> {
	struct SnakeCell {
		int x_Pos, y_Pos;
		Move NextMove;

		SnakeCell(const int& x_Pos, const int& y_Pos, Move next_move)
					: x_Pos(x_Pos), y_Pos(y_Pos), NextMove(next_move)
		{}

		void MakeMove()
		{
			this->x_Pos += NextMove.x;
			this->y_Pos += NextMove.y;
		}

		void SetNextMove(const Move& move)
		{
			this->NextMove = move;
		}
	};

	SnakeCell Head, Tail;
	unsigned int Length;
	Move LastMove;
	Move BoardOfMoves[x][y];

	Board() : Head(2, y), Tail(0, y), Length(3), LastMove(1, 0), BoardOfMoves({ Move(0, 0) })
	{
		PlaceCell(Head);
		PlaceMove(Head.x_Pos, Head.y_Pos, LastMove);

		SnakeCell* middle = new SnakeCell(1, y, &Head, &Tail);
		PlaceCell(*middle);
		PlaceMove(middle->x_Pos, middle->y_Pos, LastMove);

		PlaceCell(Tail);

		Head.next = middle;

		Tail.ahead = middle;
	}

	Board(const Board& other)
	{
		memcpy(this->coordinates, other.coordinates, sizeof(other.coordinates));
	}

	State CheckState(const Move& last_move) const
	{
		if (1) return FINISHED;

		else return RUNNING;
	}

	void Mark(const int& x, const int& y)
	{
		this->coordinates[x][y] = X;
	}

	void PlaceCell(SnakeCell cell)
	{
		Mark(cell.x_Pos, cell.y_Pos);
	}

	void ClearCell(SnakeCell cell)
	{
		this->coordinates[cell.x_Pos][cell.y_Pos] = UNOCCUPIED;
	}

	void PlaceMove(const int& x, const int& y, Move move)
	{
		this->BoardOfMoves[x][y] = move;
	}

	void OnUpdate() override
	{
		Head.SetNextMove(LastMove); // Checks for any new input by the user

		PlaceMove(Head.x_Pos, Head.y_Pos, LastMove);

		this->Head.MakeMove();

		PlaceCell(Head);

		ClearCell(Tail);

		this->Tail.MakeMove();

		this->Tail.SetNextMove(BoardOfMoves[Tail.x_Pos][Tail.y_Pos]);
	}

	void SetNextMove(const Move& move) override
	{
		LastMove = move;
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