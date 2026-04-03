#pragma once

#include "Game.h"

#include "Move.h"

#include "Player.h"

struct TicTacToe : public Game {
	struct Board;
	TicTacToe();
	static move* GetValidMoves(const Board& board);
	static letter GetCurrentLetter();
	static int CheckForDraw(const Board& board);
	static int CheckForWinner(const Board& board, const int& index, const int& CheckFor);
	static int CheckBoard(const Board& board, const int& x, const int& y);
	static void MarkOnBoard(Board& board, const int& x, const int& y, const int& letter);
	static int MakeMove(const int& x, const int& y);
	static int GetPlayerMove(move& move);
	static int TakeTurn();
	static void SetUpTurn();
	void SetUpGame();
	static void PrintBoard();
	void PrintVictoryMessage();
	static void PrintWelcomeMessage();
private:
	static Board board;
	static char CharTranslation[3];
	static int (*game_loop)();
	static Player* current_player;
	static letter current_letter;
	static Player* Players[2];
	static int isPossible(const int& X, const int& Y);
	static int isValid(const int& Coord);
	static int TakePlayerTurn(move& move);
	static int TakeAITurn(const move& last_move);
	static int PvERound();
	static int PvPRound();
	static void ToggleLetter();
	static void TogglePlayer();
	//static void ToggleTurn();
	void SetUpPvE();
	void SetUpPvP();
};


#include "Human_Player.h"
#include "AI.h"