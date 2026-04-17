#pragma once

#include "Log.h"
#include "Game.h"
#include "Move.h"
#include "Player.h"
#include "Human_Player.h"

struct Battleship : public Game {
	/* Specialized Battleship-struct for Input and Storage of a Vessel's Placement */
	struct Placement {
		int x_start;
		int x_end;
		int y_start;
		int y_end;

		Placement() : x_start(0), x_end(0), y_start(0), y_end(0) {}

		Placement(int x_start, int x_end, int y_start, int y_end)
			: x_start(x_start), x_end(x_end), y_start(y_start), y_end(y_end) {
		}

		void Sort()
		{
			int sorted[4];
			sorted[0] = (this->x_end >= this->x_start) ? this->x_start : this->x_end;
			sorted[1] = (sorted[0] == this->x_start) ? this->x_end : this->x_start;
			sorted[2] = (this->y_end >= this->y_start) ? this->y_start : this->y_end;
			sorted[3] = (sorted[2] == this->y_start) ? this->y_end : this->y_start;

			this->x_start = sorted[0];
			this->x_end = sorted[1];
			this->y_start = sorted[2];
			this->y_end = sorted[3];
		}

		bool isValid(const int& vessel_size) const
		{
			if ((this->x_start % 1 != 0 && this->x_start < 0 && this->x_start > 10) &&
				(this->x_end % 1 != 0 && this->x_end < 0 && this->x_end > 10) &&
				(this->y_start % 1 != 0 && this->y_start < 0 && this->y_start > 8) &&
				(this->y_end % 1 != 0 && this->y_end < 0 && this->y_end > 8))
			{
				Log("\nYou tried to place outside the board. Please, type your coordinates again.\n\n");
				return INVALID_PLACEMENT;
			}

			else if ((this->x_end - this->x_start) + (this->y_end - this->y_start) != (vessel_size - 1))
			{
				Log("\nYour placement did not respect the vessel's size. Please, type your coordinates again.\n\n");
				return INVALID_PLACEMENT;
			}

			else return VALID;
		}
	};

	/* Specialized Battleship Game Board */
	struct Board {
		struct Home;
		struct Moves;
		inline static const char CharTranslation[3] = { '-', 'X', 'O' };
		int coordinates[11][9];
		Board() : coordinates({ UNOCCUPIED }) {};
		Board(const Board& other)
		{
			memcpy(this->coordinates, other.coordinates, sizeof(other.coordinates));
		};
		virtual void MarkHit(const int& x, const int& y);
		void MarkMiss(const int& x, const int& y)
		{
			this->coordinates[x][y] = X;
		};
		int CheckState()
		{
			return 1;
		};
		virtual void Reset();
		void Print() const
		{
			Log("   0 1 2 3 4 5 6 7 8 9 10\n");
			Log("   ---------------------\n");

			for (int y = 8; y >= 0; y--)
			{
				std::cout << y << "| ";
				for (int x = 0; x < 11; x++)
				{
					std::cout << this->CharTranslation[this->coordinates[x][y]] << " ";
				}
				std::cout << "|" << std::endl;
			}

			Log("   ---------------------\n");
		};
	};

	/* Struct of the different boats in Battleship */
	struct Vessel;

	/* Constructor */
	Battleship();

	/* Interface */
	void SetUpGame();
	static void PrintBoard();
	static void PrintBoards();
	void End() const;
	static void Loop();
	static Battleship& Start();

private:
	/* Variables */
	static Board::Home PlayerHomeBoard[2];
	static Board::Moves PlayerMovesBoard[2];
	static void (*Gamemode)();
	static Player* Players[2];
	static int Active;
	static int Opponent;

	/* Methods */
	static int isPossible(const move& move);
	static int XisValid(const int& X);
	static int YisValid(const int& Y);
	static void MakeMove(const move& move);
	static int GetPlayerMove(move& move);
	static int TakePlayerTurn(move& move);
	static int TakeAITurn(const move& last_move);
	static void PvERound();
	static void PvPRound();
	static void TakeTurn();
	static void TogglePlayer();
	static void SetUpNextTurn();
	void SetUpBoard();
	void SetUpPvE();
	void SetUpPvP();
	static void Reset();

	/* Logging */

	void PrintVictoryMessage() const;
	static void PrintWelcomeMessage();
};