#include "BattleshipBoard.cpp"

Battleship::Homeboard Battleship::PlayerHomeboard[2];
Battleship::Hitsboard Battleship::PlayerHitsboard[2];

Battleship::Battleship() {}

void Battleship::MakeMove(const Move& Move)
{
	if (PlayerHomeboard[Opponent].CheckHit(Move.x, Move.y) == HIT)
	{
		if (PlayerHomeboard[Opponent].MarkHit(Move.x, Move.y) == true
			&& PlayerHomeboard[Opponent].CheckState() == GAME_END)
		{
			m_State = FINISHED;
		}

		PlayerHitsboard[Active].MarkHit(Move.x, Move.y);
	}

	else
	{
		PlayerHitsboard[Active].MarkMiss(Move.x, Move.y);
	}

	clear_buffer();
	std::cin.get();
}

bool Battleship::GetPlayerMove(Move& Move) const
{
	Log("Where do you wish to make a hit? (X Y)\n");
	std::cin >> Move.x >> Move.y;
	if (!PlayerHitsboard[Active].XisValid(Move.x) || !PlayerHitsboard[Active].YisValid(Move.y)) return INVALID_COORDINATE;

	else return VALID;
}

bool Battleship::TakePlayerTurn(Move& Move)
{
	if (GetPlayerMove(Move) == INVALID_COORDINATE) return INVALID_COORDINATE;

	else if (!PlayerHitsboard[Active].isPossible(Move)) return INVALID_MOVE;

	MakeMove(Move);

	return TURN_END;
}

/* TO BE REFACTORED LATER */
void Battleship::TakeAITurn(const Move& last_move)
{
	// Lorem ipsum
}

void Battleship::TogglePlayer()
{
	Active = (Active == 0) ? 1 : 0;

	Opponent = (Active == 1) ? 0 : 1;
}

void Battleship::SetUpNextTurn()
{
	ClearScreen();

	TogglePlayer();
}

/* TO BE REFACTORED LATER */
void Battleship::PvERound()
{
	// Lorem ipsum
}

void Battleship::PvPRound()
{
	PrintBoards();

	Move player_move = Move();

	while (TakePlayerTurn(player_move) != TURN_END) {};
}

void Battleship::TakeTurn()
{
	Gamemode();
}

void Battleship::SetUpBoard()
{
	std::cout << Players[Active]->GetName() << ", let's set up your board..." << std::endl << std::endl;

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
		}
		while (!placement.isValid(vessel_size));

		PlayerHomeboard[Active].PlaceVessel(current_type, placement);

		ClearScreen();
	}

	PrintBoard();
	Log("Your board has been set up!\n");

	clear_buffer();
	std::cin.get();
}

/* TO BE REFACTORED LATER */
void Battleship::SetUpPvE()
{
	// Lorem ipsum
}

void Battleship::SetUpPvP()
{
	m_Gamemode = static_cast<Gamemode>(&Battleship::PvPRound);

	Players[0] = HumanPlayer::CreatePlayer();
	Players[1] = HumanPlayer::CreatePlayer();

	TogglePlayer();
	SetUpBoard();

	TogglePlayer();
	SetUpBoard();
}

void Battleship::SetUpGame()
{
	Log("Select a match:\n1. Player vs. Player\n2. Player vs. AI\n");
	int input;
	std::cin >> input;

	SetUpPvP();

	//if (input == PvP) SetUpPvP();
	//else SetUpPvE();
}

void Battleship::Reset()
{
	PlayerHomeboard[0].Reset();
	PlayerHitsboard[0].Reset();

	PlayerHomeboard[1].Reset();
	PlayerHitsboard[1].Reset();

	Active = UNASSIGNED;

	m_State = RUNNING;
}



/*	LOGGING MEMBERS  */

void Battleship::PrintBoard() const
{
	PlayerHomeboard[Active].Print();
}

void Battleship::PrintBoards() const
{
	PlayerHitsboard[Active].Print();
	Log("   ----HITS----BOARD----\n\n");
	PlayerHomeboard[Active].Print();
	Log("   ----HOME----BOARD----\n\n");
}

void Battleship::PrintVictoryMessage() const
{
	const char* winner = Players[Active]->GetName();
	std::cout << "Congratulations, " << winner << "! You won!" << std::endl;
}

void Battleship::PrintWelcomeMessage() const
{
	Log("Let's play a game of Battleship!\n");
}



/* INTERFACE */

void Battleship::End() const
{
	PrintBoards();

	PrintVictoryMessage();
}

void Battleship::Loop()
{
	while (m_State == RUNNING)
	{
		SetUpNextTurn();

		TakeTurn();
	}
}

Battleship& Battleship::Start()
{
	static Battleship battleship = Battleship();

	if (battleship.m_State != RUNNING) battleship.Reset();

	battleship.PrintWelcomeMessage();

	battleship.SetUpGame();

	return battleship;
}



/* DESTRUCTOR */

Battleship::~Battleship() {}