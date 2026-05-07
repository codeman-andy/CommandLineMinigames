#pragma once

// Imports Game-struct and the game settings
#include "Game.h"

// Imports TicTacToeBoard struct
#include "Board/Snake.h"

// Imports the Human_Player-subclass factory
#include "Factory/HumanFactory.h"

#include <conio.h>


class Snake : public Game {
public:
	void End() override
	{
		PrintBoard();
		
		PrintVictoryMessage();

		Shutdown();
	}

	void Loop() override
	{
		while (a_State == RUNNING)
		{
			while (!_kbhit)
			{
				m_ActiveBoard->OnUpdate();
			}
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
	IBoard* m_ActiveBoard;

	Board<10, 10> m_SmallBoard;
	Board<20, 20> m_MediumBoard;
	Board<30, 30> m_LargeBoard;

	/* Override Methods */
	void SetUpGame() override
	{
		if (a_State != RUNNING) Reset();

		a_Players[0] = HumanPlayerFactory().CreatePlayer();

		a_Players[1] = nullptr;

		Log("Choose Difficulty:\n1. Easy  2. Medium  3. Expert\n");
		int input;
		std::cin >> input;

		switch (input)
		{
			case EASY:
			{
				m_ActiveBoard = &m_LargeBoard;
				break;
			}
			case MEDIUM:
			{
				m_ActiveBoard = &m_MediumBoard;
				break;
			}
			case EXPERT:
			{
				m_ActiveBoard = &m_SmallBoard;
				break;
			}
		}
	}

	void Reset() override
	{
		a_State = RUNNING;

		a_Active = UNASSIGNED;

		m_ActiveBoard->Reset();
	}

	/* Override Logging */
	void PrintBoard() const override
	{
		m_ActiveBoard->Print();
	}

	void PrintVictoryMessage() const override
	{
		const char* winner = a_Players[a_Active]->GetName();

		std::cout << "Congratulations, " << winner << "! You won!" << std::endl;
	}

	void PrintWelcomeMessage() const override { Log("Welcome to Snake!\n"); }
};