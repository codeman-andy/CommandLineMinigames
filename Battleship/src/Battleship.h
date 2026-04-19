#pragma once

#include "Log.h"
#include "Game.h"
#include "Board.h"
#include "Move.h"
#include "Human_Player.h"


struct Battleship : public Game {
	/* Specialized Battleship-struct for Input and Storage of a Vessel's Placement */
	struct Placement;

	/* Specialized Battleship Game Boards */
	struct Homeboard;
	struct Hitsboard;

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
	static Homeboard PlayerHomeboard[2];
	static Hitsboard PlayerHitsboard[2];

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
	void PrintVictoryMessage() const override;
	void PrintWelcomeMessage() const override;
};