#pragma once

// Imports Game-struct and the game settings
#include "Game.h"

// Imports TicTacToeBoard struct
#include "Board/Snake.h"

// Imports the Human_Player-subclass factory
#include "Factory/HumanFactory.h"

#include <conio.h>

#include <chrono>
#include <thread>


class Snake : public Game {
public:
	void End() override
	{
		PrintVictoryMessage();

		Shutdown();
	}

	void Loop() override
	{
		while (a_State == RUNNING)
		{
			while (!_kbhit() && a_State == RUNNING)
			{
				ClearScreen();

				a_State = m_ActiveBoard->OnUpdate();

				PrintBoard();

				// Wait for 0.5s
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}

			if (a_State != RUNNING)
			{
				// There was no key stroke. The snake crashed against the wall or itself, ending the game
				Log("\nYou have hit the wall and died!\n");

				break;
			}

			// For handling special-keys _getch() returns two separate values, the first one being 0 (0x00) or 224 (0xE0), depending on the compiler
			// Only then second return value can then properly identify the key pressed
			switch (_getch())
			{
				case 'w':
				{
					Move new_move(0, 1);
					m_ActiveBoard->SetNextMove(new_move);
					break;
				}
				case 'a':
				{
					Move new_move(-1, 0);
					m_ActiveBoard->SetNextMove(new_move);
					break;
				}
				case 's':
				{
					Move new_move(0, -1);
					m_ActiveBoard->SetNextMove(new_move);
					break;
				}
				case 'd':
				{
					Move new_move(1, 0);
					m_ActiveBoard->SetNextMove(new_move);
					break;
				}
				case 0 || 224:
				{
					int arrow_key_code = _getch();
					break;
				}
				default:
				{
					clear_buffer();
					continue;
				}
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

	/* Throwaways */
	Letter GetActiveLetter() const override { return UNOCCUPIED; };
	Letter GetOpponentLetter() const override { return UNOCCUPIED; };

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

		a_Active	 = 0;

		Log("\nChoose Difficulty:\n1. Easy  2. Medium  3. Expert\n");
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

	/* Destructor */
	~Snake()
	{}

	/* Throwaways */
	void MakeMove(const Move& Move) override {};
	bool GetPlayerMove(Move& Move) const override { return 0; };
	bool TakePlayerTurn(Move& Move) override { return 0; };
	void TakeAITurn(const Move& last_move) override {};
	void PvERound() override {};
	void PvPRound() override {};
	void TakeTurn() override {};
	void TogglePlayer() override {};
	void SetUpNextTurn() override {};
	void SetUpPvE() override {};
	void SetUpPvP() override {};
};