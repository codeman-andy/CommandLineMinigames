#pragma once

// Imports Game-struct and the game settings
#include "Game.h"

// Imports TicTacToeBoard struct
#include "BoardTicTacToe.h"

// Imports the Human_Player-subclass
#include "HPFactory.h"


/*
 * TicTacToe is a sub-class of the Game-abstract class.
 */

class TicTacToe : public Game {
public:
	/* API */
	Letter GetActiveLetter() const;
	Letter GetOpponentLetter() const;
	void End() const override;
	void Loop() override;
	void Start() override;

	/* Get singleton-instance */
	static TicTacToe* GetInstance();

private:
	/* Variables */
	Board m_Board;
	Letter m_ActiveLetter;

	/* Constructor */
	TicTacToe();

	/* Override Methods */
	void MakeMove(const Move& Move) override;
	bool GetPlayerMove(Move& Move) const override;
	bool TakePlayerTurn(Move& Move) override;
	void TakeAITurn(const Move& last_move) override;
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

	/* Destructor */
	~TicTacToe();
};


// Imports the AI-subclass (has to be at the bottom to avoid circular includes)
#include "AIFactory.h"

#include "AI.h"