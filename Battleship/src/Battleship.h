#pragma once

#include "Log.h"
#include "Game.h"
#include "Board.h"
#include "Human_Player.h"


struct Battleship : public Game {
	/* Specialized Battleship-struct for Input and Storage of a Vessel's Placement */
	struct Placement;

	/* Specialized Battleship Game Boards */
	struct Homeboard;
	struct Hitsboard;

	/* Struct of the different boats in Battleship */
	struct Vessel;

	/* Constructor */
	Battleship();

	/* Interface */
	void PrintBoards() const;
	void PrintBoard() const override;
	void End() const override;
	void Loop();
	static Battleship& Start();

private:
	/* Variables */
	static Homeboard PlayerHomeboard[2];
	static Hitsboard PlayerHitsboard[2];

	/* Methods */
	void MakeMove(const move& move) override;
	bool GetPlayerMove(move& move) const override;
	bool TakePlayerTurn(move& move) override;
	void TakeAITurn(const move& last_move) override;
	void PvERound() override;
	void PvPRound() override;
	void TakeTurn();
	void TogglePlayer();
	void SetUpNextTurn();
	void SetUpBoard();
	void SetUpPvE() override;
	void SetUpPvP() override;
	void SetUpGame() override;
	void Reset() override;

	/* Logging */
	void PrintVictoryMessage() const override;
	void PrintWelcomeMessage() const override;
};