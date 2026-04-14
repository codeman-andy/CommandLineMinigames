#include "BoardBattleship.cpp"

Battleship::Board Battleship::player_home_board[2];
Battleship::Board Battleship::player_hits_board[2];
int (*Battleship::game_loop)();
Player* Battleship::Players[2];
int Battleship::active = 3;
int Battleship::opponent;


Battleship::Battleship() {}

void Battleship::MarkOnBoard(Board& board, const int& x, const int& y)
{
	if (player_home_board[opponent].CheckHit(x, y) == HIT)
	{
		board.MarkHit(x, y);

		player_home_board[opponent].MarkHit(x, y);
	}

	else board.MarkMiss(x, y);
}

void Battleship::MakeMove(const move& move)
{
	MarkOnBoard(player_hits_board[active], move.x, move.y);
}


int Battleship::isPossible(const int& X, const int& Y)
{
	if (player_hits_board[active].coordinates[X][Y] == UNOCCUPIED) return VALID;

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

int Battleship::areInvalid(const int& vessel_size, const int& X_start, const int& Y_start, const int& X_end, const int& Y_end)
{
	if ((X_start % 1 != 0 && X_start < 0 && X_start > 10) &&
		(X_end % 1 != 0 && X_end < 0 && X_end > 10) &&
		(Y_start % 1 != 0 && Y_start < 0 && Y_start > 8) &&
		(Y_end % 1 != 0 && Y_end < 0 && Y_end > 8))
	{
		Log("\nYou tried to place outside the board. Please, type your coordinates again.\n\n");
		return INVALID_COORDINATE;
	}

	else if ((X_end - X_start) + (Y_end - Y_start) != (vessel_size - 1))
	{
		Log("\nYour placement did not respect the vessel's size. Please, type your coordinates again.\n\n");
		return INVALID_COORDINATE;
	}

	else return VALID;
}

void Battleship::Sort(int& X_start, int& X_end, int& Y_start, int& Y_end)
{
	int sorted[4];
	sorted[0] = (X_end >= X_start) ? X_start : X_end;
	sorted[1] = (sorted[0] == X_start) ? X_end : X_start;
	sorted[2] = (Y_end >= Y_start) ? Y_start : Y_end;
	sorted[3] = (sorted[2] == Y_start) ? Y_end : Y_start;

	X_start = sorted[0];
	X_end = sorted[1];
	Y_start = sorted[2];
	Y_end = sorted[3];
}

int Battleship::GetPlayerMove(move& move)
{
	Log("Where do you wish to make a hit? (X Y)\n");
	std::cin >> move.x >> move.y;
	if (!XisValid(move.x) || !YisValid(move.y)) return INVALID_COORDINATE;

	return VALID;
}

int Battleship::TakePlayerTurn(move& move)
{
	if (GetPlayerMove(move) == INVALID_COORDINATE) return INVALID_COORDINATE;

	else if (!isPossible(move.x, move.y)) return INVALID_MOVE;

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
	active = (active == 0) ? 1 : 0;

	opponent = (active == 1) ? 0 : 1;
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

int Battleship::PvPRound()
{
	PrintBoards();

	move player_move = move();

	int turn_outcome = TakePlayerTurn(player_move);

	clear_buffer();
	std::cin.get();

	if (turn_outcome != TURN_END) return turn_outcome;

	else return TURN_END;
}

int Battleship::TakeTurn()
{
	return game_loop();
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

		int x_start, y_start, x_end, y_end;
		do
		{
			std::cout << "Where do you want to place your " << vessel_name << "? (size: " << vessel_size << ")" << std::endl;
			Log("Insert four valid values separated by a whitespace <x_1 x_2 y_1 y_2>\n(i.e. <4 4 5 8>)\n");

			std::cin >> x_start >> x_end >> y_start >> y_end;

			Sort(x_start, x_end, y_start, y_end);
		}
		while (areInvalid(vessel_size, x_start, y_start, x_end, y_end));

		Placement chosen_placement(x_start, x_end, y_start, y_end);

		player_home_board[active].PlaceVessel(current_type, chosen_placement);

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
	game_loop = &PvERound;

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
	game_loop = &PvPRound;
	Players[0] = Human_Player::CreatePlayer();
	Players[1] = Human_Player::CreatePlayer();
}

void Battleship::SetUpGame()
{
	Log("Select a match:\n1. Player vs. Player\n2. Player vs. AI\n");
	int input;
	std::cin >> input;

	SetUpPvP();

	//if (input == PvP) SetUpPvP();

	//else SetUpPvE();

	TogglePlayer();
	SetUpBoard();

	TogglePlayer();
	SetUpBoard();
}

void Battleship::Reset()
{
	player_home_board[0].Reset();
	player_hits_board[0].Reset();

	player_home_board[1].Reset();
	player_hits_board[1].Reset();

	active = 3;
	opponent = 3;

	STATE = RUNNING;
}



/*	LOGGING MEMBERS  */

void Battleship::PrintBoard()
{
	player_home_board[active].Print();
}

void Battleship::PrintBoards()
{
	player_hits_board[active].Print();
	Log("   ----HITS----BOARD----\n\n");
	player_home_board[active].Print();
	Log("   ----HOME----BOARD----\n\n");
}

void Battleship::PrintVictoryMessage() const
{
	const char* winner = Players[active]->GetName();
	std::cout << "Congratulations, " << winner << "! You won!" << std::endl;
}

void Battleship::PrintWelcomeMessage()
{
	Log("Let's play a game of Battleship!\n");
}



/* INTERFACE */

void Battleship::End() const
{
	Battleship::PrintBoard();

	PrintVictoryMessage();
}

void Battleship::Loop()
{
	while (STATE == RUNNING)
	{
		SetUpNextTurn();

		while (TakeTurn() != TURN_END) {};
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