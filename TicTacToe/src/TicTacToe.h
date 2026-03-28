#pragma once

struct move {
	size_t x;
	size_t y;

	move() : x(0), y(0) {}

	move(size_t X, size_t Y) {
		x = X;
		y = Y;
	}

	bool operator==(move& other) {
		return (x == other.x && y == other.y);
	}

	bool operator!=(move& other) {
		return (x != other.x || y != other.y);
	}
};

enum letter : size_t { UNOCCUPIED, X, O };

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

struct TicTacToe : public Game {
	TicTacToe();
	static letter GetCurrentLetter();
	static int MakeMove(size_t x, size_t y);
	static int GetPlayerMove(move& move);
	static int TakeTurn();
	static void SetUpTurn();
	void SetUpGame();
	static void PrintBoard();
	void PrintVictoryMessage();
	static void PrintWelcomeMessage();
private:
	static size_t board[3][3];
	static size_t rows[3];
	static size_t cols[3];
	static size_t diagonals[2];
	static char CharTranslation[3];
	static int (*game_mode)();
	static Player* current_player;
	static letter current_letter;
	static Player* Players[2];
	static int CheckForWinner(size_t index, size_t CheckFor);
	static int UpdateAndCheckBoard(size_t x, size_t y);
	static void MarkOnBoard(size_t x, size_t y);
	static int isPossible(size_t X, size_t Y);
	static int isValid(size_t Coord);
	//static int TakePlayerTurn();
	//static int TakeAITurn();
	static int PvERound();
	static int PvPRound();
	static void ToggleLetter();
	static void TogglePlayer();
	//static void ToggleTurn();
	void SetUpPvE();
	void SetUpPvP();
};