#pragma once

#include "Game.h"
#include "Player.h"
#include "Human_Player.h"

#define INVALID_COORDINATE 0
#define INVALID_MOVE 0

#define EMPTY 0
#define FULL 3

#define CheckForRow 0
#define CheckForCol 1
#define CheckForDiagLeft 2
#define CheckForDiagRight 3

enum letter : size_t { UNOCCUPIED, X, O };

struct TicTacToe : Game {
	size_t board[3][3];
	size_t rows[3];
	size_t cols[3];
	size_t diagonals[2];
	char CharTranslation[3];
	letter current_letter;
	//(int (*func)())* turns[2];
	int (TicTacToe::*turns[2])();
	int (TicTacToe::*current_turn)();
	Player* Players[2];
	Player* current_player;
	TicTacToe();
	int CheckForWinner(size_t index, size_t CheckFor);
	int UpdateBoard(size_t x, size_t y);
	void MarkOnBoard(size_t x, size_t y);
	int MakeMove(size_t X, size_t Y);
	int isPossible(size_t X, size_t Y);
	int isValid(size_t coord);
	int GetPlayerMove(size_t& X, size_t& Y);
	int TakeTurn();
	void SetLetter();
	void SetPlayer();
	void SetUpTurn();
	void SetUpPlayers();
	void SetUpGame();
	void PrintBoard();
	void PrintVictoryMessage();
	static void PrintWelcomeMessage();
};