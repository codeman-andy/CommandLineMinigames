#pragma once

// Imports Move-struct which will store a single TicTacToe Move
#include "Move.h"

class IGame {
	/* Methods */
	virtual void MakeMove(const Move& Move) = 0;
	virtual bool GetPlayerMove(Move& Move) const = 0;
	virtual bool TakePlayerTurn(Move& Move) = 0;
	virtual void TakeAITurn(const Move& last_move) = 0;
	virtual void PvERound() = 0;
	virtual void PvPRound() = 0;
	virtual void TakeTurn() = 0;
	virtual void TogglePlayer() = 0;
	virtual void SetUpNextTurn() = 0;
	virtual void SetUpPvE() = 0;
	virtual void SetUpPvP() = 0;
	virtual void SetUpGame() = 0;
	virtual void Reset() = 0;
	virtual void PrintVictoryMessage() const = 0;
	virtual void PrintWelcomeMessage() const = 0;

	/* Interface */
	virtual void PrintBoard() const = 0;
	virtual void End() const = 0;
	virtual void Loop() = 0;
};