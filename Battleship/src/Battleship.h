#pragma once

#include "../../TicTacToe/src/Game.h"
#include "../../TicTacToe/src/Move.h"
#include "../../TicTacToe/src/Player.h"

enum vessel_type { Carrier, Battle_Ship, Destroyer, Submarine, Patrol_Boat };

struct Battleship : public Game {
	/* Specialized Battleship Game Board */
	struct Board;

	/* Struct of the different boats in Battleship */
	struct Vessel;

	/* Constructor */
	Battleship();

	/* Interface */
	static void MarkOnBoard(Board& board, const int& x, const int& y);
	static int TakeTurn();
	void SetUpGame();
	static void PrintBoard();
	void PrintVictoryMessage() const;
	static void PrintWelcomeMessage();

private:
	/* Variables */
	static Board board;
	static char CharTranslation[3];
	static int (*game_loop)();
	static Player* Players[2];
	static Player* current_player;

	/* Methods */
	static int isPossible(const int& X, const int& Y);
	static int isValid(const int& Coord);
	static int MakeMove(const int& x, const int& y);
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
};


#include "../../TicTacToe/src/Human_Player.h"
#include "../../TicTacToe/src/AI.h"