#pragma once

#include "Log.h"
#include "Game.h"
#include "Board.h"
#include "HumanPlayer.h"


class Battleship : public Game {
public:
	/* Specialized Battleship-struct for Input and Storage of a Vessel's Placement */
	struct Placement;

	/* Specialized Battleship Game Boards */
	struct Homeboard;
	struct Hitsboard;

	/* Struct of the different boats in Battleship */
	struct Vessel;

	/* API */
	void End() const override;
	void Loop() override;
	static Battleship& Start();

	/* Destructor */
	~Battleship();

private:
	/* Variables */
	static Homeboard PlayerHomeboard[2];
	static Hitsboard PlayerHitsboard[2];

	/* Constructor */
	Battleship();

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
	void SetUpBoard();

	/* Logging */
	void PrintBoard() const override;
	void PrintVictoryMessage() const override;
	void PrintWelcomeMessage() const override;

	/* Additional Logging */
	void PrintBoards() const;
};