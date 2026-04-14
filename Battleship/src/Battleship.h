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
	static void MarkOnBoard(Board& board, const int& x, const int& y);
	static int TakeTurn();
	void SetUpGame();
	static void PrintBoard();
	static void PrintBoards();
	void PrintVictoryMessage() const;
	static void PrintWelcomeMessage();
	void End() const;
	static void Loop();
	static Battleship& Start();

private:
	/* Variables */
	static Board::Home player_home_board[2];
	static Board::Moves player_hits_board[2];
	static int (*game_loop)();
	static Player* Players[2];
	static int active;
	static int opponent;

	/* Methods */
	static int isPossible(const int& X, const int& Y);
	static int XisValid(const int& X);
	static int YisValid(const int& Y);
	static int areInvalid(const int& vessel_size, const int& X_start, const int& Y_start, const int& X_end, const int& Y_end);
	static void Sort(int& X_start, int& X_end, int& Y_start, int& Y_end);
	static void MakeMove(const move& move);
	static int GetPlayerMove(move& move);
	static int TakePlayerTurn(move& move);
	static int TakeAITurn(const move& last_move);
	static int PvERound();
	static int PvPRound();
	static void TogglePlayer();
	static void SetUpNextTurn();
	void SetUpBoard();
	void SetUpPvE();
	void SetUpPvP();
	static void Reset();
};