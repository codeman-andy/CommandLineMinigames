#include "BattleshipBoard.cpp"

Battleship::Homeboard Battleship::PlayerHomeboard[2];
Battleship::Hitsboard Battleship::PlayerHitsboard[2];

Battleship::Battleship() {}

void Battleship::MakeMove(const move& move)
{
	if (PlayerHomeboard[Opponent].CheckHit(move.x, move.y) == HIT)
	{
		if (PlayerHomeboard[Opponent].MarkHit(move.x, move.y) == true
			&& PlayerHomeboard[Opponent].CheckState() == GAME_END)
		{
			STATE = FINISHED;
		}

		PlayerHitsboard[Active].MarkHit(move.x, move.y);
	}

	else
	{
		PlayerHitsboard[Active].MarkMiss(move.x, move.y);
	}

	clear_buffer();
	std::cin.get();
}

bool Battleship::GetPlayerMove(move& move) const
{
	Log("Where do you wish to make a hit? (X Y)\n");
	std::cin >> move.x >> move.y;
	if (!PlayerHitsboard[Active].XisValid(move.x) || !PlayerHitsboard[Active].YisValid(move.y)) return INVALID_COORDINATE;

	else return VALID;
}

bool Battleship::TakePlayerTurn(move& move)
{
	if (GetPlayerMove(move) == INVALID_COORDINATE) return INVALID_COORDINATE;

	else if (!PlayerHitsboard[Active].isPossible(move)) return INVALID_MOVE;

	MakeMove(move);

	return TURN_END;
}

/* TO BE REFACTORED LATER */
void Battleship::TakeAITurn(const move& last_move)
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

	move player_move = move();

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
		vessel_type current_type = static_cast<vessel_type>(type);

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

	Players[0] = Human_Player::CreatePlayer();
	Players[1] = Human_Player::CreatePlayer();

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

	STATE = RUNNING;
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
	while (STATE == RUNNING)
	{
		SetUpNextTurn();

		TakeTurn();
	}
}

Battleship& Battleship::Start()
{
	static Battleship battleship = Battleship();

	if (battleship.STATE != RUNNING) battleship.Reset();

	battleship.PrintWelcomeMessage();

	battleship.SetUpGame();

	return battleship;
}



/* DESTRUCTOR */

Battleship::~Battleship() {}