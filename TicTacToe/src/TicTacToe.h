#pragma once

// Imports Game-struct and the game settings
#include "Game.h"

// Imports Move-struct which will store a single TicTacToe move
#include "Move.h"

// Imports Player-class
#include "Player.h"


/*
 * TicTacToe is a public sub-struct of the Game-struct.
 */

struct TicTacToe : public Game {
	/* Specialized Tic-Tac-Toe Game Board */
	struct Board;

	/* Constructor */
	TicTacToe();

	/* Interface */
	static letter GetActiveLetter();
	static letter GetOpponentLetter();
	static void PrintBoard();
	void End() const;
	static void Loop();
	static TicTacToe& Start();

private:
	/* Variables */
	static Board s_Board;
	static void (*Gamemode)();
	static Player* Players[2];
	static int Active;
	static int Opponent;
	static letter ActiveLetter;

	/* Methods */
	static int isPossible(const move& move);
	static int isValid(const int& Coord);
	static void MakeMove(const move& move);
	static int GetPlayerMove(move& move);
	static int TakePlayerTurn(move& move);
	static void TakeAITurn(const move& last_move);
	static void PvERound();
	static void PvPRound();
	static void TakeTurn();
	static void ToggleLetter();
	static void TogglePlayer();
	static void SetUpNextTurn();
	void SetUpPvE();
	void SetUpPvP();
	static void Reset();
	void SetUpGame();

	/* Logging */
	static void PrintDrawMessage();
	void PrintVictoryMessage() const;
	static void PrintWelcomeMessage();
};


// Imports the Human_Player-subclass
#include "Human_Player.h"

// Imports the AI-subclass
#include "AI.h"