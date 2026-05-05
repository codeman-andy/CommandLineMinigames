#pragma once

// Imports Game-struct and the game settings
#include "Game.h"

// Imports the Battleship gameboard
#include "Board/Battleship.h"

// Imports the Human_Player-subclass factory
#include "Factory/HumanFactory.h"


/*
 * Battleship is a sub-class of the Game-abstract class.
 */

class Battleship : public Game {
public:
	/* API */
	void End() override
	{
		PrintBoards();

		PrintVictoryMessage();

		Shutdown();
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
	static Game* GetInstance();

private:
	/* Variables */
	Homeboard m_PlayerHomeboard[2];
	Hitsboard m_PlayerHitsboard[2];

	/* Constructor */
	Battleship() : Game(),
				   m_PlayerHomeboard({ Homeboard() }),
				   m_PlayerHitsboard({ Hitsboard() })
	{}

	/* Override Methods */
	void MakeMove(const Move& Move) override
	{
		if (m_PlayerHomeboard[a_Opponent].CheckHit(Move.x, Move.y) == HIT)
		{
			if (m_PlayerHomeboard[a_Opponent].MarkHit(Move.x, Move.y) == true
				&& m_PlayerHomeboard[a_Opponent].CheckState() == GAME_END)
			{
				a_State = FINISHED;
			}

			m_PlayerHitsboard[a_Active].MarkHit(Move.x, Move.y);
		}

		else
		{
			m_PlayerHitsboard[a_Active].MarkMiss(Move.x, Move.y);
		}

		clear_buffer();
		std::cin.get();
	}

	bool GetPlayerMove(Move& Move) const override
	{
		Log("Where do you wish to make a hit? (X Y)\n");
		std::cin >> Move.x >> Move.y;
		if (!m_PlayerHitsboard[a_Active].XisValid(Move.x) || !m_PlayerHitsboard[a_Active].YisValid(Move.y)) return INVALID_COORDINATE;

		else return VALID;
	}

	bool TakePlayerTurn(Move& Move) override
	{
		if (GetPlayerMove(Move) == INVALID_COORDINATE) return INVALID_COORDINATE;

		else if (!m_PlayerHitsboard[a_Active].isPossible(Move)) return INVALID_MOVE;

		MakeMove(Move);

		return TURN_END;
	}

	void TakeAITurn(const Move& last_move) override
	{
		// Lorem ipsum
	}

	void PvERound() override
	{
		// Lorem ipsum
	}

	void PvPRound() override
	{
		PrintBoards();

		Move player_move = Move();

		while (TakePlayerTurn(player_move) != TURN_END) {};
	}

	void TakeTurn() override
	{
		Gamemode();
	}

	void TogglePlayer() override
	{
		a_Active = (a_Active == 0) ? 1 : 0;

		a_Opponent = (a_Active == 1) ? 0 : 1;
	}

	void SetUpNextTurn() override
	{
		ClearScreen();

		TogglePlayer();
	}

	void SetUpPvE() override
	{
		// Lorem ipsum
	}

	void SetUpPvP() override
	{
		a_Gamemode = static_cast<Gamemode>(&Battleship::PvPRound);

		a_Players[0] = HumanPlayerFactory().CreatePlayer();

		a_Players[1] = HumanPlayerFactory().CreatePlayer();

		TogglePlayer();
		SetUpBoard();

		TogglePlayer();
		SetUpBoard();
	}

	void SetUpGame() override
	{
		Log("Select a match:\n1. Player vs. Player\n2. Player vs. AI\n");
		int input;
		std::cin >> input;

		SetUpPvP();

		//if (input == PvP) SetUpPvP();
		//else SetUpPvE();
	}

	void Reset() override
	{
		if (a_State != RUNNING) Reset();

		m_PlayerHomeboard[0].Reset();
		m_PlayerHitsboard[0].Reset();

		m_PlayerHomeboard[1].Reset();
		m_PlayerHitsboard[1].Reset();

		a_Active = UNASSIGNED;

		a_State = RUNNING;
	}

	/* Additional Methods */
	void SetUpBoard()
	{
		ClearScreen();

		std::cout << a_Players[a_Active]->GetName() << ", let's set up your board..." << std::endl;

		std::cin.get();
		clear_buffer();

		for (int type = CARRIER; type <= PATROL_BOAT; type++)
		{
			VesselType current_type = static_cast<VesselType>(type);

			PrintBoard();

			Log("\nVessels may be placed either horizontally or vertically.\n");

			const char* vessel_name = Vessel::GetVesselName(current_type);
			const int vessel_size = Vessel::GetVesselSize(current_type);

			Placement placement;
			do
			{
				std::cout << "Where do you want to place your " << vessel_name << "? (size: " << vessel_size << ")" << std::endl;
				Log("Insert four valid values separated by a whitespace <x_1 x_2 y_1 y_2>\n(i.e. <4 4 5 8>)\n");

				std::cin >> placement.x_start >> placement.x_end >> placement.y_start >> placement.y_end;

				placement.Sort();
			} while (!placement.isValid(vessel_size) || !m_PlayerHomeboard[a_Active].isPossible(placement));

			m_PlayerHomeboard[a_Active].PlaceVessel(current_type, placement);

			ClearScreen();

			std::cout << a_Players[a_Active]->GetName() << ", let's set up your board..." << std::endl << std::endl;
		}

		PrintBoard();
		Log("\nYour board has been set up!\n");

		clear_buffer();
		std::cin.get();
	}

	/* Logging */
	void PrintBoard() const override { m_PlayerHomeboard[a_Active].Print();	}

	void PrintVictoryMessage() const override
	{
		const char* winner = a_Players[a_Active]->GetName();
		std::cout << "Congratulations, " << winner << "! You won!" << std::endl;
	}

	void PrintWelcomeMessage() const override
	{
		Log("Let's play a game of Battleship!\n");
	}

	/* Additional Logging */
	void PrintBoards() const
	{
		m_PlayerHitsboard[a_Active].Print();
		Log("   ----HITS----BOARD----\n\n");
		m_PlayerHomeboard[a_Active].Print();
		Log("   ----HOME----BOARD----\n\n");
	}

	/* Destructor */
	~Battleship()
	{}

	/* Unused Override Members */
	Letter GetActiveLetter() const override { return O; }
	Letter GetOpponentLetter() const override { return O; }
};