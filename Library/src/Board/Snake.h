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

	SnakeCell Head = SnakeCell(2, 0, Move(1, 0));
	SnakeCell Tail = SnakeCell(0, 0, Move(1, 0));
	unsigned int Length = 3;
	Move LastMove = Move(1, 0);
	Move BoardOfMoves[x][y];
	void (Board::* food_gen_algorithm)() = &Board::GenerateFoodBasic;

	Board() : BoardOfMoves({ Move(0, 0) })
	{
		PlaceCell(Head);
		PlaceMove(Head.x_Pos, Head.y_Pos, LastMove);

		SnakeCell* middle = new SnakeCell(1, 0, Move(1, 0));
		PlaceCell(*middle);
		PlaceMove(middle->x_Pos, middle->y_Pos, LastMove);

		PlaceCell(Tail);

		GenerateFood();
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

	void GenerateFoodBasic()
	{
		int random_x_index = rand() % (x - 1);
		int random_y_index = rand() % (y - 1);

		while (this->coordinates[random_x_index][random_y_index] != UNOCCUPIED)
		{
			int random_x_index = rand() % (x - 1);
			int random_y_index = rand() % (y - 1);
		}

		this->coordinates[random_x_index][random_y_index] = O;
	}

	void GenerateFood()
	{
		(this->*food_gen_algorithm)();

		//if (this->Length >= (x * y / 2))
		//	food_gen_algorithm = &Board::SomeGenFood;
	}

	State OnUpdate() override
	{
		Head.SetNextMove(LastMove); // Checks for any new input by the user

		PlaceMove(Head.x_Pos, Head.y_Pos, LastMove);

		this->Head.MakeMove();

		if (OutOfBounds())
		{
			return FINISHED;
		}

		if (hasEaten())
		{
			Grow();

			GenerateFood();
		}
		else
		{
			PlaceCell(Head);

			ClearCell(Tail);

			this->Tail.MakeMove();

			this->Tail.SetNextMove(BoardOfMoves[Tail.x_Pos][Tail.y_Pos]);
		}

		return RUNNING;
	}

	void Grow()
	{
		PlaceCell(Head);

		this->Length++;
	}

	bool hasEaten()
	{
		return (this->coordinates[Head.x_Pos][Head.y_Pos] == O);
	}

	bool OutOfBounds()
	{
		return !(Head.x_Pos >= 0 &&
				 Head.x_Pos < x  &&
				 Head.y_Pos >= 0 &&
				 Head.y_Pos < y);
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
	}

	~Board()
	{}
};