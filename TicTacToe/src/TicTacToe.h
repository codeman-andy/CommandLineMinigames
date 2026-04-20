#pragma once

// Imports Game-struct and the game settings
#include "Game.h"

#include "Board.h"


/*
 * TicTacToe is a public sub-struct of the Game-struct.
 */

struct TicTacToe : public Game {
	/* Specialized Tic-Tac-Toe Game Board */
	struct Board;

	/* Constructor */
	TicTacToe();

	/* Interface */
	static letter GetActiveLetter();
	static letter GetOpponentLetter();
	void PrintBoard() const override;
	void End() const override;
	void Loop();
	static TicTacToe& Start();

private:
	/* Variables */
	static Board s_Board;
	static letter ActiveLetter;

	/* Methods */
	void MakeMove(const move& move) override;
	bool GetPlayerMove(move& move) const override;
	bool TakePlayerTurn(move& move) override;
	void TakeAITurn(const move& last_move) override;
	void PvERound() override;
	void PvPRound() override;
	void TakeTurn();
	void ToggleLetter();
	void TogglePlayer();
	void SetUpNextTurn();
	void SetUpPvE() override;
	void SetUpPvP() override;
	void SetUpGame() override;
	void Reset() override;

	/* Logging */
	void PrintDrawMessage() const;
	void PrintVictoryMessage() const override;
	void PrintWelcomeMessage() const override;
};


// Imports the Human_Player-subclass
#include "Human_Player.h"

// Imports the AI-subclass
#include "AI.h"