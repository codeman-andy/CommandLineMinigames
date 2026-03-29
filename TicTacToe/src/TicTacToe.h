#pragma once

struct move {
	int x;
	int y;

	move() : x(0), y(0) {}

	move(int X, int Y) {
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

enum letter { UNOCCUPIED, X, O };

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
	move* GetValidMoves();
	static letter GetCurrentLetter();
	static int CheckForDraw();
	static int MakeMove(int x, int y);
	static int GetPlayerMove(move& move);
	static int TakeTurn();
	static void SetUpTurn();
	void SetUpGame();
	static void PrintBoard();
	void PrintVictoryMessage();
	static void PrintWelcomeMessage();
private:
	static int board[3][3];
	static int rows[3];
	static int cols[3];
	static int diagonals[2];
	static char CharTranslation[3];
	static int (*game_mode)();
	static Player* current_player;
	static letter current_letter;
	static Player* Players[2];
	static int CheckForWinner(int index, int CheckFor);
	static int UpdateAndCheckBoard(int x, int y);
	static void MarkOnBoard(int x, int y);
	static int isPossible(int X, int Y);
	static int isValid(int Coord);
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