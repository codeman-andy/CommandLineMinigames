#pragma once

// Imports Game-struct and the game settings
#include "Game.h"

// Imports TicTacToeBoard struct
#include "BoardTicTacToe.h"

// Imports the Human_Player-subclass factory
#include "HPFactory.h"


/*
 * TicTacToe is a sub-class of the Game-abstract class.
 */

class TicTacToe : public Game {
public:
	/* API */
	Letter GetActiveLetter() const { return m_ActiveLetter; }

	Letter GetOpponentLetter() const { return (m_ActiveLetter == O) ? X : O; }

	void End() const override
	{
		PrintBoard();

		if (a_State == DRAW) PrintDrawMessage();

		else PrintVictoryMessage();
	}

	void Loop() override
	{
		while (a_State == RUNNING)
		{
			SetUpNextTurn();

			TakeTurn();
		}
	}

	void Start() override
	{
		PrintWelcomeMessage();

		SetUpGame();
	}

	/* Get singleton-instance */
	static TicTacToe* GetInstance();

private:
	/* Variables */
	Board m_Board;
	Letter m_ActiveLetter;

	/* Constructor */
	TicTacToe() : Game(),
				  m_Board(Board()),
				  m_ActiveLetter(UNOCCUPIED)
	{}

	/* Override Methods */
	void MakeMove(const Move& Move) override
	{
		m_Board.Mark(Move.x, Move.y, m_ActiveLetter);

		a_State = m_Board.CheckState(Move);
	}

	bool GetPlayerMove(Move& Move) const override
	{
		Log("Where do you wish to place? (vertically)\n");
		std::cin >> Move.y;
		if (!m_Board.YisValid(Move.y)) return INVALID_COORDINATE;

		Log("Where do you wish to place? (horizontally)\n");
		std::cin >> Move.x;
		if (!m_Board.XisValid(Move.x)) return INVALID_COORDINATE;

		else return VALID;
	}

	bool TakePlayerTurn(Move& Move) override
	{
		if (GetPlayerMove(Move) == INVALID_COORDINATE) return INVALID_COORDINATE;

		else if (!m_Board.isPossible(Move)) return INVALID_MOVE;

		MakeMove(Move);

		return TURN_END;
	}

	void TakeAITurn(const Move& last_move) override
	{
		AI* bot = (AI*)a_Players[a_Active];

		bot->RemoveFromValidMoves(last_move);

		const char* bot_name = bot->GetName();

		std::cout << "It's  " << bot_name << "'s turn! ";

		Move ai_move = bot->MakeMove(m_Board);

		std::cout << bot_name << " picked [" << ai_move.x << ", " << ai_move.y << "]" << std::endl;

		MakeMove(ai_move);

		bot->RemoveFromValidMoves(ai_move);
	}

	void PvERound() override
	{
		PrintBoard();

		Move player_move = Move();

		while (TakePlayerTurn(player_move) != TURN_END) {};

		if (a_State != RUNNING) return;

		else SetUpNextTurn();

		TakeAITurn(player_move);
	}

	void PvPRound() override
	{
		PrintBoard();

		Move player_move = Move();

		while (TakePlayerTurn(player_move) != TURN_END) {};
	}

	void TakeTurn() override
	{
		(this->*a_Gamemode)();
	}

	void TogglePlayer() override
	{
		a_Active = (a_Active == 0) ? 1 : 0;

		a_Opponent = (a_Active == 1) ? 0 : 1;
	}

	void SetUpNextTurn() override
	{
		TogglePlayer();
		ToggleLetter();
	}

	void SetUpPvE() override
	{
		a_Gamemode = static_cast<Gamemode>(&TicTacToe::PvERound);

		a_Players[0] = HumanPlayerFactory().CreatePlayer();

		AI* bot = static_cast<AI*>(AIFactory().CreatePlayer());

		bot->SetValidMoves(m_Board.GetValidMoves(), m_Board.nr_of_available_moves);

		a_Players[1] = bot;
	}

	void SetUpPvP() override
	{
		a_Gamemode = static_cast<Gamemode>(&TicTacToe::PvPRound);

		a_Players[0] = HumanPlayerFactory().CreatePlayer();

		a_Players[1] = HumanPlayerFactory().CreatePlayer();
	}

	void SetUpGame() override
	{
		if (a_State != RUNNING) Reset();

		Log("Select a match:\n1. Player vs. Player\n2. Player vs. AI\n");
		int input;
		std::cin >> input;

		if (input == PvP) SetUpPvP();

		else SetUpPvE();
	}

	void Reset() override
	{
		a_State = RUNNING;

		a_Active = UNASSIGNED;

		m_Board.Reset();

		m_ActiveLetter = UNOCCUPIED;
	}

	/* Additional Methods */
	void ToggleLetter() { m_ActiveLetter = (m_ActiveLetter == X) ? O : X; }

	/* Override Logging */
	void PrintBoard() const override { m_Board.Print(); }

	void PrintVictoryMessage() const override
	{
		const char* winner = a_Players[a_Active]->GetName();

		std::cout << "Congratulations, " << winner << "! You won!" << std::endl;
	}

	void PrintWelcomeMessage() const override {	Log("Let's play a game of Tic-Tac-Toe!\n");	}

	/* Additional Logging */
	void PrintDrawMessage() const {	Log("The game ended with no victor...\n"); }

	/* Destructor */
	~TicTacToe()
	{}
};


// Imports the AI-subclass (has to be at the bottom to avoid circular includes)
#include "AIFactory.h"

#include "AI.h"