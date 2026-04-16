#include "BoardTicTacToe.cpp"

TicTacToe::Board TicTacToe::board;
void (*TicTacToe::s_Gamemode)();
Player* TicTacToe::Players[2];
int TicTacToe::active;
int TicTacToe::opponent;
letter TicTacToe::current_letter;

TicTacToe::TicTacToe() {}

letter TicTacToe::GetCurrentLetter()
{
	return current_letter;
}

letter TicTacToe::GetOpponentLetter()
{
	return (current_letter == O) ? X : O;
}

void TicTacToe::MarkOnBoard(Board& board, const int& x, const int& y, const int& letter)
{
	board.coordinates[x][y] = letter;
	board.row_counter[y] += 1;
	board.col_counter[x] += 1;

	if (x == y) board.diagonal_counter[0]++;

	if (x + y == 2) board.diagonal_counter[1]++;

	board.nr_of_available_moves--;
}

void TicTacToe::MakeMove(const move& move)
{
	board.Mark(move.x, move.y, current_letter);

	STATE = board.CheckState(move);
}

int TicTacToe::isPossible(const move& move)
{
	if (board.coordinates[move.x][move.y] == UNOCCUPIED) return VALID;

	else Log("The coordinate you tried to mark is already occupied. Please, choose another.\n");
	return INVALID_MOVE;
}

int TicTacToe::isValid(const int& Coord)
{
	if (Coord % 1 == 0 && Coord >= 0 && Coord <= 2) return VALID;

	else Log("Your last coordinate was invalid. Please, type your coordinates again.\n");
	return INVALID_COORDINATE;
}

int TicTacToe::GetPlayerMove(move& move)
{
	Log("Where do you wish to place? (vertically)\n");
	std::cin >> move.y;
	if (!isValid(move.y)) return INVALID_COORDINATE;

	Log("Where do you wish to place? (horizontally)\n");
	std::cin >> move.x;
	if (!isValid(move.x)) return INVALID_COORDINATE;

	else return VALID;
}

int TicTacToe::TakePlayerTurn(move& move)
{

	if (GetPlayerMove(move) == INVALID_COORDINATE) return INVALID_COORDINATE;

	else if (!isPossible(move)) return INVALID_MOVE;

	MakeMove(move);

	return TURN_END;
}

int TicTacToe::TakeAITurn(const move& last_move)
{
	AI* bot = (AI*) Players[active];

	bot->RemoveFromValidMoves(last_move);

	const char* bot_name = bot->GetName();

	std::cout << "It's  " << bot_name << "'s turn! ";

	move ai_move = bot->MakeMove(board);

	std::cout << bot_name << " chose [" << ai_move.x << ", " << ai_move.y << "]" << std::endl;

	MakeMove(ai_move);

	bot->RemoveFromValidMoves(ai_move);

	return TURN_END;
}

void TicTacToe::ToggleLetter()
{
	current_letter = (current_letter == X) ? O : X;
}

void TicTacToe::TogglePlayer()
{
	active = (active == 0) ? 1 : 0;

	opponent = (active == 1) ? 0 : 1;
}

void TicTacToe::SetUpNextTurn()
{
	TogglePlayer();
	ToggleLetter();
}

void TicTacToe::PvERound()
{
	PrintBoard();

	move player_move = move();

	while (TakePlayerTurn(player_move) != TURN_END) {};

	if (STATE != RUNNING) return;

	SetUpNextTurn();

	TakeAITurn(player_move);
}

void TicTacToe::PvPRound()
{
	PrintBoard();

	move player_move = move();

	while (TakePlayerTurn(player_move) != TURN_END) {};
}

void TicTacToe::TakeTurn()
{
	return s_Gamemode();
}

void TicTacToe::SetUpPvE()
{
	s_Gamemode = &PvERound;

	Players[0] = Human_Player::CreatePlayer();

	Log("Choose Difficulty:\n1. Easy  2. Medium  3. Expert\n");
	int input;
	std::cin >> input;

	difficulty chosen_difficulty = static_cast<difficulty>(input);

	const char* name = (chosen_difficulty == EASY) ? "Pam" : (chosen_difficulty == MEDIUM) ? "Donald J. Trump" : "Peter Thiel";

	AI* bot = AI::CreatePlayer(name, chosen_difficulty);

	bot->SetValidMoves(board.GetValidMoves(), board.nr_of_available_moves);

	Players[1] = bot;
}

void TicTacToe::SetUpPvP()
{
	s_Gamemode = &PvPRound;
	Players[0] = Human_Player::CreatePlayer();
	Players[1] = Human_Player::CreatePlayer();
}

void TicTacToe::SetUpGame()
{
	Log("Select a match:\n1. Player vs. Player\n2. Player vs. AI\n");
	int input;
	std::cin >> input;

	if (input == PvP) SetUpPvP();

	else SetUpPvE();
}

void TicTacToe::Reset()
{
	board.Reset();

	active = 3;

	current_letter = UNOCCUPIED;

	STATE = RUNNING;
}



/*	LOGGING MEMBERS  */

void TicTacToe::PrintBoard()
{
	board.Print();
}

void TicTacToe::PrintDrawMessage()
{
	Log("The game ended with no victor...\n");
}

void TicTacToe::PrintVictoryMessage() const
{
	const char* winner = Players[active]->GetName();
	std::cout << "Congratulations, " << winner << "! You won!" << std::endl;
}

void TicTacToe::PrintWelcomeMessage()
{
	Log("Let's play a game of Tic-Tac-Toe!\n");
}



/* INTERFACE */

void TicTacToe::End() const
{
	PrintBoard();

	if (STATE == DRAW) PrintDrawMessage();

	else PrintVictoryMessage();
}

void TicTacToe::Loop()
{
	while (STATE == RUNNING)
	{
		SetUpNextTurn();

		TakeTurn();
	}
}

TicTacToe& TicTacToe::Start()
{
	if (STATE != RUNNING) Reset();

	PrintWelcomeMessage();

	static TicTacToe tictactoe = TicTacToe();

	tictactoe.SetUpGame();

	return tictactoe;
}