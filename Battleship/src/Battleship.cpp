#include "BoardBattleship.cpp"

Battleship::Board Battleship::player_home_board[2];
Battleship::Board Battleship::player_hits_board[2];
int (*Battleship::game_loop)();
Player* Battleship::Players[2];
int Battleship::current;
int Battleship::opponent;


Battleship::Battleship() {}

void Battleship::MarkOnBoard(Board& board, const int& x, const int& y)
{
	board.coordinates[x][y] = player_home_board[opponent].CheckHit(x, y) ? O : X;
}

int Battleship::MakeMove(const int& x, const int& y)
{
	MarkOnBoard(player_hits_board[current], x, y);

	if (player_home_board[opponent].nr_of_vessels == 0)
	{
		STATE = WINNER_FOUND;
		return WINNER_FOUND;
	}

	return RUNNING;
}


int Battleship::isPossible(const int& X, const int& Y)
{
	if (player_hits_board[current].coordinates[Y][X] == UNOCCUPIED) return RUNNING;

	else Log("You have already made a hit on that coordinate. Please, pick another.\n");
	return INVALID_MOVE;
}

int Battleship::XisValid(const int& X)
{
	if (X % 1 == 0 && X >= 0 && X < 11) return RUNNING;

	else Log("Your last coordinate was invalid. Please, type the coordinates again.\n");
	return INVALID_COORDINATE;
}

int Battleship::YisValid(const int& Y)
{
	if (Y % 1 == 0 && Y >= 0 && Y < 9) return RUNNING;

	else Log("Your last coordinate was invalid. Please, type the coordinates again.\n");
	return INVALID_COORDINATE;
}

int Battleship::areValid(const int& X_start, const int& Y_start, const int& X_end, const int& Y_end)
{
	if ((X_start % 1 == 0 && X_start >= 0 && X_start <= 10) &&
		(X_end % 1 == 0 && X_end >= 0 && X_end <= 10) &&
		(Y_start % 1 == 0 && Y_start >= 0 && Y_start <= 8) &&
		(Y_end % 1 == 0 && Y_end >= 0 && Y_end <= 8))
		return RUNNING;

	else Log("Your placement is invalid. Please, type your coordinates again.\n");
	return INVALID_COORDINATE;
}

int Battleship::GetPlayerMove(move& move)
{
	Log("Where do you wish to make a hit? (X Y)\n");
	std::cin >> move.x >> move.y;
	if (!XisValid(move.x) || !YisValid(move.y)) return INVALID_COORDINATE;

	return RUNNING;
}

int Battleship::TakePlayerTurn(move& move)
{
	if (GetPlayerMove(move) == INVALID_COORDINATE) return INVALID_COORDINATE;

	else if (!isPossible(move.x, move.y)) return INVALID_MOVE;

	if (MakeMove(move.x, move.y) == WINNER_FOUND) return WINNER_FOUND;

	return RUNNING;
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
	current = (current == 0) ? 1 : 0;

	opponent = (opponent == 1) ? 0 : 1;
}

void Battleship::SetUpNextTurn()
{
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
	PrintBoard();

	move player_move = move();

	int outcome = TakePlayerTurn(player_move);

	if (!outcome) return outcome;

	SetUpNextTurn();

	return RUNNING;
}

int Battleship::TakeTurn()
{
	return game_loop();
}

void Battleship::SetUpBoard(const int& player_index)
{
	for (int current_type = CARRIER; current_type < 5; current_type++)
	{
		int x_start, y_start, x_end, y_end;
		do
		{
			PrintBoard();
			Log("Vessels may be placed either horizontally or vertically.\n");
			std::cout << "Where do you want to place your " << Vessel::vessel_names[current_type] << "?" << std::endl;
			Log("Insert four valid values separated by a whitespace <x_1 y_1 x_2 y_2>\n(i.e. <4 5 4 8>)\n");

			std::cin >> x_start >> y_start >> x_end >> y_end;
		}
		while (!areValid(x_start, y_start, x_end, y_end));

		Placement placement(x_start, x_end, y_start, y_end);

		player_home_board[player_index].PlaceVessel(current_type, placement);
	}

	PrintBoard();
	Log("Your board has been set up!\n");
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

	SetUpBoard(0);
	SetUpBoard(1);

	SetUpNextTurn();
}

void Battleship::Reset()
{
	for (int i = 0; i < 2; i++)
	{
		player_home_board[i].Reset();
		player_hits_board[i].Reset();
	}

	current = 3;
	opponent = 3;
}



/*	LOGGING MEMBERS  */

void Battleship::PrintBoard()
{
	player_home_board[0].Print();
}

void Battleship::PrintVictoryMessage() const {
	const char* winner = Players[current]->GetName();
	std::cout << "Congratulations, " << winner << "! You won!" << std::endl;
}

void Battleship::PrintWelcomeMessage() {
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
	while (STATE == RUNNING) TakeTurn();
}

Battleship& Battleship::Start()
{
	STATE = RUNNING;

	if (!player_home_board[0].isEmpty()) Reset();

	PrintWelcomeMessage();

	static Battleship game = Battleship();

	game.SetUpGame();

	return game;
}