#pragma once

#include "../../TicTacToe/src/Game.h"
#include "../../TicTacToe/src/Move.h"
#include "../../TicTacToe/src/Player.h"

enum vessel_type { CARRIER, BATTLESHIP, DESTROYER, SUBMARINE, PATROL_BOAT };

struct Battleship : public Game {
	/* Specialized Battleship Game Board */
	struct Board;

	/* Struct of the different boats in Battleship */
	struct Vessel;

	/* Constructor */
	Battleship();

	/* Interface */
	static void MarkOnBoard(Board& board, const int& x, const int& y);
	static int TakeTurn();
	void SetUpGame();
	static void PrintBoard();
	void PrintVictoryMessage() const;
	static void PrintWelcomeMessage();
	void End() const;
	static void Loop();
	static Battleship& Start();

private:
	/* Variables */
	static Board player_home_board[2];
	static Board player_hits_board[2];
	static int (*game_loop)();
	static Player* Players[2];
	static Player* current_player;

	/* Methods */
	static int isPossible(const int& X, const int& Y);
	static int isValid(const int& Coord);
	static int areValid(const int& X_start, const int& Y_start, const int& X_end, const int& Y_end);
	static int MakeMove(const int& x, const int& y);
	static int GetPlayerMove(move& move);
	static int TakePlayerTurn(move& move);
	static int TakeAITurn(const move& last_move);
	static int PvERound();
	static int PvPRound();
	static void TogglePlayer();
	static void SetUpNextTurn();
	void SetUpBoard();
	void SetUpPvE();
	void SetUpPvP();
	static void Reset();
};


#include "../../TicTacToe/src/Human_Player.h"
#include "../../TicTacToe/src/AI.h"