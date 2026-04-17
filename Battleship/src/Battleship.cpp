#include "BoardBattleship.cpp"

Battleship::Board::Home Battleship::PlayerHomeBoard[2];
Battleship::Board::Moves Battleship::PlayerMovesBoard[2];
void (*Battleship::Gamemode)();
Player* Battleship::Players[2];
int Battleship::Active = 3;
int Battleship::Opponent;


Battleship::Battleship() {}

void Battleship::MakeMove(const move& move)
{
	if (PlayerHomeBoard[Opponent].CheckHit(move.x, move.y) == HIT)
	{
		PlayerHomeBoard[Opponent].MarkHit(move.x, move.y);

		PlayerMovesBoard[Active].MarkHit(move.x, move.y);
	}

	else
	{
		PlayerMovesBoard[Active].MarkMiss(move.x, move.y);
	}

	clear_buffer();
	std::cin.get();
}


int Battleship::isPossible(const move& move)
{
	if (PlayerMovesBoard[Active].coordinates[move.x][move.y] == UNOCCUPIED) return VALID;

	else Log("You have already made a hit on that coordinate. Please, pick another.\n");
	return INVALID_MOVE;
}

int Battleship::XisValid(const int& X)
{
	if (X % 1 == 0 && X >= 0 && X < 11) return VALID;

	else Log("Your last coordinate was invalid. Please, type the coordinates again.\n");
	return INVALID_COORDINATE;
}

int Battleship::YisValid(const int& Y)
{
	if (Y % 1 == 0 && Y >= 0 && Y < 9) return VALID;

	else Log("Your last coordinate was invalid. Please, type the coordinates again.\n");
	return INVALID_COORDINATE;
}

int Battleship::GetPlayerMove(move& move)
{
	Log("Where do you wish to make a hit? (X Y)\n");
	std::cin >> move.x >> move.y;
	if (!XisValid(move.x) || !YisValid(move.y)) return INVALID_COORDINATE;

	else return VALID;
}

int Battleship::TakePlayerTurn(move& move)
{
	if (GetPlayerMove(move) == INVALID_COORDINATE) return INVALID_COORDINATE;

	else if (!isPossible(move)) return INVALID_MOVE;

	MakeMove(move);

	return TURN_END;
}

/* TO BE REFACTORED LATER
int Battleship::TakeAITurn(const move& last_move) {
	AI* bot = (AI*)current_player;

	bot->RemoveFromValidMoves(last_move);

	std::cout << "It's  " << bot->GetName() << "'s turn! ";

	move ai_move = bot->MakeMove(board);

	std::cout << bot->GetName() << " chose [" << ai_move.x << ", " << ai_move.y << "]" << std::endl;

	if (MakeMove(ai_move.x, ai_move.y) == WINNER_FOUND) return WINNER_FOUND;

	bot->RemoveFromValidMoves(ai_move);

	return RUNNING;
}
*/

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

/*
int Battleship::PvERound()
{
	PrintBoard();

	move player_move = move();

	int outcome = TakePlayerTurn(player_move);

	if (!outcome) return outcome;

	SetUpNextTurn();

	if (TakeAITurn(player_move) == WINNER_FOUND) return WINNER_FOUND;

	SetUpNextTurn();

	return RUNNING;
}
*/

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

		PlayerHomeBoard[Active].PlaceVessel(current_type, placement);

		ClearScreen();
	}

	PrintBoard();
	Log("Your board has been set up!\n");

	clear_buffer();
	std::cin.get();
}

/* TO BE REFACTORED LATER
void Battleship::SetUpPvE()
{
	Gamemode = &PvERound;

	Players[0] = Human_Player::CreatePlayer();

	Log("Choose Difficulty:\n1. Easy  2. Medium  3. Expert\n");
	int input;
	std::cin >> input;

	difficulty chosen_difficulty = static_cast<difficulty>(input);

	const char* name = (chosen_difficulty == EASY) ? "Pam" : (chosen_difficulty == MEDIUM) ? "Donald J. Trump" : "Peter Thiel";

	AI* bot_player = AI::CreatePlayer(name, chosen_difficulty);

	bot_player->SetValidMoves(board.GetValidMoves(), board.nr_of_available_moves);

	Players[1] = bot_player;
}
*/

void Battleship::SetUpPvP()
{
	Gamemode = &PvPRound;

	Players[0] = Human_Player::CreatePlayer();
	TogglePlayer();
	SetUpBoard();

	Players[1] = Human_Player::CreatePlayer();
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
	PlayerHomeBoard[0].Reset();
	PlayerMovesBoard[0].Reset();

	PlayerHomeBoard[1].Reset();
	PlayerMovesBoard[1].Reset();

	Active = 3;

	STATE = RUNNING;
}



/*	LOGGING MEMBERS  */

void Battleship::PrintBoard()
{
	PlayerHomeBoard[Active].Print();
}

void Battleship::PrintBoards()
{
	PlayerMovesBoard[Active].Print();
	Log("   ----HITS----BOARD----\n\n");
	PlayerHomeBoard[Active].Print();
	Log("   ----HOME----BOARD----\n\n");
}

void Battleship::PrintVictoryMessage() const
{
	const char* winner = Players[Active]->GetName();
	std::cout << "Congratulations, " << winner << "! You won!" << std::endl;
}

void Battleship::PrintWelcomeMessage()
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
	if (STATE != RUNNING) Reset();

	PrintWelcomeMessage();

	static Battleship battleship = Battleship();

	battleship.SetUpGame();

	return battleship;
}