#pragma once

// Imports Game-struct and the game settings
#include "Game.h"

// Imports Game::Board abstract struct
#include "Board.h"


/*
 * TicTacToe is a public sub-struct of the Game-struct.
 */

class TicTacToe : public Game {
public:
	/* Specialized Tic-Tac-Toe Game Board */
	struct Board;

	/* API */
	static Letter GetActiveLetter();
	static Letter GetOpponentLetter();
	void End() const override;
	void Loop() override;
	static TicTacToe& Start();

	/* Destructor */
	~TicTacToe();

private:
	/* Variables */
	static Board s_Board;
	static Letter ActiveLetter;

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
};


// Imports the Human_Player-subclass
#include "HumanPlayer.h"

// Imports the AI-subclass
#include "AI.h"