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
	static int CheckForDraw();
	static int CheckForWinner(const Board& board, const int& index, const int& CheckFor);
	static int CheckBoard(const Board& board, const int& x, const int& y);
	static void MarkOnBoard(Board& board, const int& x, const int& y, const int& letter);
	static int TakeTurn();
	void SetUpGame();
	static void PrintBoard();
	static void PrintDrawMessage();
	void PrintVictoryMessage() const;
	static void PrintWelcomeMessage();
	void End();
	static void Loop();
	static TicTacToe& Start();

private:
	/* Variables */
	static Board board;
	static char CharTranslation[3];
	static int (*game_loop)();
	static int turn_number;
	static Player* Players[2];
	static Player* current_player;
	static letter current_letter;

	/* Methods */
	static int isPossible(const int& X, const int& Y);
	static int isValid(const int& Coord);
	static int MakeMove(const int& x, const int& y);
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
};


// Imports the Human_Player-subclass.
#include "Human_Player.h"

// Imports the AI-subclass.
#include "AI.h"