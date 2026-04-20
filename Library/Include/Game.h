#pragma once

// Imports the game settings
#include "Settings.h"

// Imports Player-class
#include "Player.h"

// Imports Move-struct which will store a single TicTacToe move
#include "Move.h"

// Imports Printable-interface
#include "Printable.h"

/*
 * The Game-superclass that all minigames will inherit
 * There will always only be one Game-instance at any given moment
 * Each game will present a state between RUNNING, WINNER_FOUND, or DRAW
 */

struct Game {
	/* Gameboard */
	template <unsigned int x, unsigned int y>
	struct Board;

	typedef void (Game::*Gamemode)();

	/* Variables */
	state STATE;
	Gamemode m_Gamemode;
	Player* Players[2];
	int Active;
	int Opponent;

	/* Constructor*/
	Game();

	/* Methods */
	virtual void MakeMove(const move& move) = 0;
	virtual bool GetPlayerMove(move& move) const = 0;
	virtual bool TakePlayerTurn(move& move) = 0;
	virtual void TakeAITurn(const move& last_move) = 0;
	virtual void PvERound() = 0;
	virtual void PvPRound() = 0;
	virtual void SetUpPvE() = 0;
	virtual void SetUpPvP() = 0;
	virtual void SetUpGame() = 0;
	virtual void Reset() = 0;
	virtual void PrintVictoryMessage() const = 0;
	virtual void PrintWelcomeMessage() const = 0;

	/* Interface */
	virtual void PrintBoard() const = 0;
	virtual void End() const = 0;
	static void Loop();
};