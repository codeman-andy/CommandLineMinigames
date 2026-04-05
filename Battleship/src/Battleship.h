#pragma once

#include "../../TicTacToe/src/Game.h"
#include "../../TicTacToe/src/Move.h"
#include "../../TicTacToe/src/Player.h"

struct Battleship : public Game {
	/* Specialized Tic-Tac-Toe Game Board */
	struct Board;

	/* Constructor */
	Battleship();

	/* Interface */
	static move* GetValidMoves(const Board& board);
	static int CheckForWinner(const Board& board, const int& index, const int& CheckFor);
	static int CheckBoard(const Board& board, const int& x, const int& y);
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
	void SetUpPvE();
	void SetUpPvP();
};


#include "../../TicTacToe/src/Human_Player.h"
#include "../../TicTacToe/src/AI.h"