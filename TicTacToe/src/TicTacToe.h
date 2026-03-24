#pragma once

struct coords {
	size_t x;
	size_t y;
};

#include "Game.h"
#include "Player.h"
#include "Human_Player.h"
#include "AI.h"

#define INVALID_COORDINATE 0
#define INVALID_MOVE 0

#define EMPTY 0
#define FULL 3

#define CheckForRow 0
#define CheckForCol 1
#define CheckForDiagLeft 2
#define CheckForDiagRight 3

enum letter : size_t { UNOCCUPIED, X, O };

struct TicTacToe : public Game {
	static size_t board[3][3];
	static size_t rows[3];
	static size_t cols[3];
	static size_t diagonals[2];
	static char CharTranslation[3];
	static int (*current_turn)();
	static Player* current_player;
	static letter current_letter;
	//(int (*func)())* turns[2];
	int (*turns[2])();
	Player* Players[2];
	TicTacToe();
	static int CheckForWinner(size_t index, size_t CheckFor);
	static int UpdateBoard(size_t x, size_t y);
	static void MarkOnBoard(size_t x, size_t y);
	static int MakeMove(size_t x, size_t y);
	static int isPossible(size_t X, size_t Y);
	static int isValid(size_t Coord);
	static int GetPlayerMove(size_t& X, size_t& Y);
	static int TakePlayerTurn();
	static int TakeAITurn();
	static int TakeTurn();
	void ToggleLetter();
	void TogglePlayer();
	void ToggleTurn();
	void SetUpTurn();
	void SetUpPvE();
	void SetUpPvP();
	void SetUpGame();
	void PrintBoard();
	void PrintVictoryMessage();
	static void PrintWelcomeMessage();
};