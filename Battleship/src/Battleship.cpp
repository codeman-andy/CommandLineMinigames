#include "BoardBattleship.cpp"

Battleship::Board Battleship::player_home_board[2];
Battleship::Board Battleship::player_hits_board[2];
int (*Battleship::game_loop)();
Player* Battleship::current_player;
Player* Battleship::Players[2];


Battleship::Battleship() {}

void Battleship::MarkOnBoard(Board& board, const int& x, const int& y)
{
	board.coordinates[y][x] = X;
}

/* TO BE REFACTORED
int Battleship::MakeMove(const int& x, const int& y)
{
	MarkOnBoard(board, x, y);

	if (board.CheckState() == WINNER_FOUND)
	{
		STATE = WINNER_FOUND;
		return WINNER_FOUND;
	}

	return RUNNING;
}
*/

int Battleship::isPossible(const int& X, const int& Y)
{
	if (board.coordinates[Y][X] == UNOCCUPIED) return RUNNING;

	else Log("The coordinate you tried to mark is already occupied. Please, choose another.\n");
	return INVALID_MOVE;
}

int Battleship::isValid(const int& Coord)
{
	if (Coord % 1 == 0 && Coord >= 0 && Coord <= 2) return RUNNING;

	else Log("Your last coordinate was invalid. Please, type your coordinates again.\n");
	return INVALID_COORDINATE;
}

int Battleship::areValid(const int& X_start, const int& Y_start, const int& X_end, const int& Y_end)
{
	if ((X_start % 1 == 0 && X_start >= 1 && X_start <= 9) &&
		(X_end % 1 == 0 && X_end >= 1 && X_end <= 9) &&
		(Y_start % 1 == 0 && Y_start >= 1 && Y_start <= 11) &&
		(Y_end % 1 == 0 && Y_end >= 1 && Y_end <= 11))
		return RUNNING;

	else Log("Your placement is invalid. Please, type your coordinates again.\n");
	return INVALID_COORDINATE;
}

int Battleship::GetPlayerMove(move& move)
{
	Log("Where do you wish to place? (vertically)\n");
	std::cin >> move.y;
	if (!isValid(move.y)) return INVALID_COORDINATE;

	Log("Where do you wish to place? (horizontally)\n");
	std::cin >> move.x;
	if (!isValid(move.x)) return INVALID_COORDINATE;

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
	current_player = (current_player == Players[0]) ? Players[1] : Players[0];
}

void Battleship::SetUpNextTurn()
{
	TogglePlayer();
}

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

void Battleship::SetUpBoard()
{
	for (int current_type = CARRIER; current_type < 5; current_type++)
	{
		int x_start, y_start, x_end, y_end;
		do
		{
			Log("Vessels may be placed either horizontally of vertically.\n");
			std::cout << "Where do you want to place your " << Vessel::vessel_names[current_type] << "?" << std::endl;
			Log("Insert four valid values separated by a whitespace (i.e. <4 5 4 8>)\n");

			std::cin >> x_start >> y_start >> x_end >> y_end;
		}
		while (!areValid(x_start, y_start, x_end, y_end));


	}
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

	SetUpBoard();

	SetUpNextTurn();
}

void Battleship::Reset()
{
	for (int i = 0; i < 2; i++)
	{
		player_home_board[i].Reset();
		player_hits_board[i].Reset();
	}

	current_player = nullptr;
}



/*	LOGGING MEMBERS  */

void Battleship::PrintBoard()
{
	player_home_board[0].Print();
}

void Battleship::PrintVictoryMessage() const {
	const char* winner = current_player->GetName();
	std::cout << "Congratulations, " << winner << "! You won!" << std::endl;
}

void Battleship::PrintWelcomeMessage() {
	Log("Let's play a game of Tic-Tac-Toe!");
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