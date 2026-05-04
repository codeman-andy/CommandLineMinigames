#pragma once

// Imports Game-struct and the game settings
#include "Game.h"

// Imports Board abstract struct
#include "Board.h"

// Imports the Human_Player-subclass factory
#include "HPFactory.h"


/*
 * Battleship is a sub-class of the Game-abstract class.
 */

class Battleship : public Game {
public:
	/* Specialized Battleship-struct for Input and Storage of a Vessel's Placement */
	struct Placement {
		int x_start;
		int x_end;
		int y_start;
		int y_end;

		Placement() : x_start(0), x_end(0), y_start(0), y_end(0) {}

		Placement(int x_start, int x_end, int y_start, int y_end)
			: x_start(x_start), x_end(x_end), y_start(y_start), y_end(y_end)
		{
		}

		void Sort()
		{
			int sorted[4];
			sorted[0] = (this->x_end >= this->x_start) ? this->x_start : this->x_end;
			sorted[1] = (sorted[0] == this->x_start) ? this->x_end : this->x_start;
			sorted[2] = (this->y_end >= this->y_start) ? this->y_start : this->y_end;
			sorted[3] = (sorted[2] == this->y_start) ? this->y_end : this->y_start;

			this->x_start = sorted[0];
			this->x_end = sorted[1];
			this->y_start = sorted[2];
			this->y_end = sorted[3];
		}

		bool isValid(const int& vessel_size) const
		{
			if ((this->x_start % 1 != 0 && this->x_start < 0 && this->x_start > 10) &&
				(this->x_end % 1 != 0 && this->x_end < 0 && this->x_end > 10) &&
				(this->y_start % 1 != 0 && this->y_start < 0 && this->y_start > 8) &&
				(this->y_end % 1 != 0 && this->y_end < 0 && this->y_end > 8))
			{
				Log("\nYou tried to place outside the board. Please, type your coordinates again.\n\n");
				return INVALID_PLACEMENT;
			}

			else if ((this->x_end - this->x_start) + (this->y_end - this->y_start) != (vessel_size - 1))
			{
				Log("\nYour placement did not respect the vessel's size. Please, type your coordinates again.\n\n");
				return INVALID_PLACEMENT;
			}

			else return VALID;
		}
	};

	/* Struct of the different boats in Battleship */
	struct Vessel {
		inline static const char* const Name[5] = { "Carrier", "Battleship", "Destroyer", "Submarine", "Patrol Boat" };
		inline static const int Size[5] = { 5, 4, 3, 3, 2 };
		VesselType type;
		int size;
		int hit_points;

		Vessel() : type(BATTLESHIP), size(32), hit_points(32) {}

		Vessel(VesselType type, int size) : type(type), size(size), hit_points(size) {}

		static Vessel PatrolBoat()
		{
			return Vessel(PATROL_BOAT, 2);
		}

		static Vessel Submarine()
		{
			return Vessel(SUBMARINE, 3);
		}

		static Vessel Destroyer()
		{
			return Vessel(DESTROYER, 3);
		}

		static Vessel Battleship()
		{
			return Vessel(BATTLESHIP, 4);
		}

		static Vessel Carrier()
		{
			return Vessel(CARRIER, 5);
		}

		static const char* GetVesselName(const VesselType& type)
		{
			return Name[type];
		}

		static const int GetVesselSize(const VesselType& type)
		{
			return Size[type];
		}

		void Hit()
		{
			this->hit_points--;
		}

		void Reset()
		{
			this->hit_points = this->size;
		}
	};

	/* Specialized Battleship Game Boards */
	struct Homeboard : public Gameboard<11, 9> {
		int nr_of_vessels;
		Vessel vessels[5];
		Placement placements[5];

		Homeboard() : nr_of_vessels(5), placements()
		{
			vessels[CARRIER] = Vessel::Carrier();
			vessels[BATTLESHIP] = Vessel::Battleship();
			vessels[DESTROYER] = Vessel::Destroyer();
			vessels[SUBMARINE] = Vessel::Submarine();
			vessels[PATROL_BOAT] = Vessel::PatrolBoat();
		}

		Homeboard(const Homeboard& other) : nr_of_vessels(other.nr_of_vessels)
		{
			memcpy(this->coordinates, other.coordinates, sizeof(other.coordinates));
			memcpy(this->vessels, other.vessels, sizeof(other.vessels));
			memcpy(this->placements, other.placements, sizeof(other.placements));
		}

		bool isEmpty() const
		{
			return (this->nr_of_vessels == 0);
		}

		bool isFull() const
		{
			return (this->nr_of_vessels == 5);
		}

		State CheckState() const
		{
			if (this->isEmpty()) return FINISHED;

			else return RUNNING;
		}

		void PlaceHorizontally(const int& x_start, const int& x_end, const int& y)
		{
			for (int x = x_start; x <= x_end; x++)
			{
				this->coordinates[x][y] = X;
			}
		}

		void PlaceVertically(const int& x, const int& y_start, const int& y_end)
		{
			for (int y = y_start; y <= y_end; y++)
			{
				this->coordinates[x][y] = X;
			}
		}

		void PlaceVessel(const VesselType& VesselType, const Placement& placement)
		{
			this->placements[VesselType] = placement;

			if (placement.x_start == placement.x_end) PlaceVertically(placement.x_start, placement.y_start, placement.y_end);

			else PlaceHorizontally(placement.x_start, placement.x_end, placement.y_start);
		}

		VesselType IdentifyVessel(const int& x, const int& y) const
		{
			int type = 0;
			while ((x < this->placements[type].x_start || x > this->placements[type].x_end)
				|| (y < this->placements[type].y_start || y > this->placements[type].y_end))
			{
				type++;
			}
			return static_cast<VesselType>(type);
		}

		bool MarkHit(const int& x, const int& y)
		{
			this->coordinates[x][y] = O;

			VesselType type = IdentifyVessel(x, y);

			this->vessels[type].Hit();

			if (this->vessels[type].hit_points == 0)
			{
				std::cout << "The " << Vessel::Name[type] << " has been destroyed!\n";

				this->nr_of_vessels--;

				return VESSEL_DESTROYED;
			}

			else return VESSEL_SURVIVED;
		}

		void MarkMiss(const int& x, const int& y)
		{
			this->coordinates[x][y] = X;
		}

		int CheckHit(const int& x, const int& y) const
		{
			if (this->coordinates[x][y] == UNOCCUPIED)
			{
				Log("Miss!\n");
				return MISS;
			}

			else
			{
				Log("You have hit a ship!\n");
				return HIT;
			}
		}

		void Reset() override
		{
			for (int x = 0; x < 11; x++)
			{
				for (int y = 0; y < 9; y++)
				{
					this->coordinates[x][y] = UNOCCUPIED;
				}
			}

			for (int i = 0; i < 5; i++)
			{
				this->vessels[i].Reset();
			}

			this->nr_of_vessels = 5;
		}

		bool isPossible(Placement placement)
		{
			bool is_possible = true;

			for (int x = placement.x_start; x <= placement.x_end; x++)
			{
				for (int y = placement.y_start; y <= placement.y_end; y++)
				{
					if (this->coordinates[x][y] != UNOCCUPIED)
					{
						Log("There already is a ship there. Please, pick a different spot.\n");
						is_possible = false;
						break;
					}
				}
			}

			return is_possible;
		}

		void Print() const override
		{
			Log("   0 1 2 3 4 5 6 7 8 9 10\n");
			Log("   ---------------------\n");

			for (int y = 8; y >= 0; y--)
			{
				std::cout << y << "| ";
				for (int x = 0; x < 11; x++)
				{
					std::cout << CharTranslation[this->coordinates[x][y]] << " ";
				}
				std::cout << "|" << std::endl;
			}

			Log("   ---------------------\n");
		}

		~Homeboard() {}
	};

	struct Hitsboard : Gameboard<11, 9> {

		void MarkHit(const int& x, const int& y)
		{
			this->coordinates[x][y] = O;
		}

		void MarkMiss(const int& x, const int& y)
		{
			this->coordinates[x][y] = X;
		}

		void Print() const override
		{
			Log("   0 1 2 3 4 5 6 7 8 9 10\n");
			Log("   ---------------------\n");

			for (int y = 8; y >= 0; y--)
			{
				std::cout << y << "| ";
				for (int x = 0; x < 11; x++)
				{
					std::cout << CharTranslation[this->coordinates[x][y]] << " ";
				}
				std::cout << "|" << std::endl;
			}

			Log("   ---------------------\n");
		}

		~Hitsboard() {}
	};

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
		std::cout << a_Players[a_Active]->GetName() << ", let's set up your board..." << std::endl << std::endl;

		for (int type = CARRIER; type < PATROL_BOAT; type++)
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
		}

		PrintBoard();
		Log("Your board has been set up!\n");

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