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
	static letter GetCurrentLetter();
	static void MarkOnBoard(Board& board, const int& x, const int& y, const int& letter);
	static int TakeTurn();
	static void PrintBoard();
	void End() const;
	static void Loop();
	static TicTacToe& Start();

private:
	/* Variables */
	static Board board;
	static int (*game_loop)();
	static Player* Players[2];
	static Player* current_player;
	static letter current_letter;

	/* Methods */
	static bool CheckForDraw();
	static int isPossible(move& move);
	static int isValid(const int& Coord);
	static int MakeMove(const move& move);
	static int GetPlayerMove(move& move);
	static int TakePlayerTurn(move& move);
	static int TakeAITurn(const move& last_move);
	static int PvERound();
	static int PvPRound();
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


// Imports the Human_Player-subclass.
#include "Human_Player.h"

// Imports the AI-subclass.
#include "AI.h"