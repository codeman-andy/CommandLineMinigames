#pragma once

// Imports Game-struct and the game settings
#include "Game.h"

// Imports Game::Board abstract struct
#include "Board.h"


/*
 * TicTacToe is a public sub-struct of the Game-struct.
 */

struct TicTacToe : public Game {
	/* Specialized Tic-Tac-Toe Game Board */
	struct Board;

	/* API */
	static letter GetActiveLetter();
	static letter GetOpponentLetter();
	void End() const override;
	void Loop() override;
	static TicTacToe& Start();

private:
	/* Variables */
	static Board s_Board;
	static letter ActiveLetter;

	/* Constructor */
	TicTacToe();

	/* Override Methods */
	void MakeMove(const move& move) override;
	bool GetPlayerMove(move& move) const override;
	bool TakePlayerTurn(move& move) override;
	void TakeAITurn(const move& last_move) override;
	void PvERound() override;
	void PvPRound() override;
	void TakeTurn() override;
	void TogglePlayer() override;
	void SetUpNextTurn() override;
	void SetUpPvE() override;
	void SetUpPvP() override;
	void SetUpGame() override;
	void Reset() override;

	/* Additional Methods */
	void ToggleLetter();

	/* Logging */
	void PrintBoard() const override;
	void PrintVictoryMessage() const override;
	void PrintWelcomeMessage() const override;

	/* Additional Logging */
	void PrintDrawMessage() const;
};


// Imports the Human_Player-subclass
#include "Human_Player.h"

// Imports the AI-subclass
#include "AI.h"