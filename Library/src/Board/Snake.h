#pragma once

// Imports the Board-abstract-struct
#include "Board.h"

#include "RealTime.h"


/* Specialized Snake Game Board */
template <unsigned int x, unsigned int y>
struct Board : public RealTime<x, y> {
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

	SnakeCell Head = SnakeCell(2, 0, Move(1, 0));
	SnakeCell Tail = SnakeCell(0, 0, Move(1, 0));
	unsigned int Length = 3;
	Move BoardOfMoves[x][y];

	/*
	 * 'LastMove' is a non-dependent name.Non-dependent names are looked up and associated with a declaration immediately,
	 * whereas dependent names (i.e. 'this->LastMove') aren't until the template they depend on is instantiated.
	 * 
	 * Non-dependent name lookup doesn't check inside base class templates (dependent base classes), because the contents
	 * of that class can change depending on which specialization is chosen.
	 * 
	 * Hence, if here we used 'LastMove' it would send off a compiler error, and 'this->LastMove' must be used instead.
	 */

	Board() : BoardOfMoves({ Move(0, 0) })
	{
		PlaceCell(Head);
		PlaceMove(Head.x_Pos, Head.y_Pos, this->LastMove);

		SnakeCell* middle = new SnakeCell(1, 0, Move(1, 0));
		PlaceCell(*middle);
		PlaceMove(middle->x_Pos, middle->y_Pos, this->LastMove);

		PlaceCell(Tail);

		GenerateFood();
	}

	Board(const Board& other)
	{
		memcpy(this->coordinates, other.coordinates, sizeof(other.coordinates));
	}

	unsigned int GetLength() const
	{
		return Length;
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

	void GenerateFood()
	{
		int random_x_index;
		int random_y_index;

		do
		{
			random_x_index = rand() % (x - 1);
			random_y_index = rand() % (y - 1);
		} while (this->coordinates[random_x_index][random_y_index] != UNOCCUPIED);

		this->coordinates[random_x_index][random_y_index] = O;
	}

	State OnUpdate() override
	{
		Head.SetNextMove(this->LastMove); // Checks for any new input by the user

		PlaceMove(Head.x_Pos, Head.y_Pos, this->LastMove);

		this->Head.MakeMove();

		if (OutOfBounds())
		{
			Print();

			Log("\nYou have hit the wall and died!\n");
			return FINISHED;
		}

		else if (HitItself())
		{
			Print();

			Log("\nYou have hit yourself and died!\n");
			return FINISHED;
		}

		else if (HasEaten())
		{
			Grow();

			GenerateFood();
		}
		else
		{
			ClearCell(Tail);

			this->Tail.MakeMove();

			this->Tail.SetNextMove(BoardOfMoves[Tail.x_Pos][Tail.y_Pos]);
		}

		PlaceCell(Head);

		Print();

		return RUNNING;
	}

	void Grow()
	{
		this->Length++;
	}

	bool HasEaten()
	{
		return (this->coordinates[Head.x_Pos][Head.y_Pos] == O);
	}

	bool HitItself()
	{
		return (this->coordinates[Head.x_Pos][Head.y_Pos] == X);
	}

	bool OutOfBounds() const override
	{
		return !(Head.x_Pos >= 0 &&
				 Head.x_Pos < x  &&
				 Head.y_Pos >= 0 &&
				 Head.y_Pos < y);
	}

	void PrintFrame() const
	{
		Log("  ");

		for (int i = 0; i < x; i++)
			Log("-");

		Log("\n");
	}

	void PrintScore() const
	{
		Log("\nYour current score is: ");
		Log(Length - 3);
		Log("\n");
	}

	void Print() const override
	{
		PrintFrame();

		for (int row = (y - 1); row >= 0; row--)
		{
			std::cout << "| ";
			for (int col = 0; col < x; col++)
			{
				std::cout << CharTranslation[this->coordinates[col][row]];
			}
			std::cout << "|" << std::endl;
		}

		PrintFrame();

		PrintScore();
	}

	~Board()
	{}
};