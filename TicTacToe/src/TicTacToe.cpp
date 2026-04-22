#include "TicTacToeBoard.cpp"

TicTacToe::Board TicTacToe::s_Board;
Letter TicTacToe::ActiveLetter;

TicTacToe::TicTacToe() {}

Letter TicTacToe::GetActiveLetter()
{
	return ActiveLetter;
}

Letter TicTacToe::GetOpponentLetter()
{
	return (ActiveLetter == O) ? X : O;
}

void TicTacToe::MakeMove(const Move& Move)
{
	s_Board.Mark(Move.x, Move.y, ActiveLetter);

	m_State = s_Board.CheckState(Move);
}

bool TicTacToe::GetPlayerMove(Move& Move) const
{
	Log("Where do you wish to place? (vertically)\n");
	std::cin >> Move.y;
	if (!s_Board.YisValid(Move.y)) return INVALID_COORDINATE;

	Log("Where do you wish to place? (horizontally)\n");
	std::cin >> Move.x;
	if (!s_Board.XisValid(Move.x)) return INVALID_COORDINATE;

	else return VALID;
}

bool TicTacToe::TakePlayerTurn(Move& Move)
{
	if (GetPlayerMove(Move) == INVALID_COORDINATE) return INVALID_COORDINATE;

	else if (!s_Board.isPossible(Move)) return INVALID_MOVE;

	MakeMove(Move);

	return TURN_END;
}

void TicTacToe::TakeAITurn(const Move& last_move)
{
	AI* bot = (AI*) Players[Active];

	bot->RemoveFromValidMoves(last_move);

	const char* bot_name = bot->GetName();

	std::cout << "It's  " << bot_name << "'s turn! ";

	Move ai_move = bot->MakeMove(s_Board);

	std::cout << bot_name << " picked [" << ai_move.x << ", " << ai_move.y << "]" << std::endl;

	MakeMove(ai_move);

	bot->RemoveFromValidMoves(ai_move);
}

void TicTacToe::ToggleLetter()
{
	ActiveLetter = (ActiveLetter == X) ? O : X;
}

void TicTacToe::TogglePlayer()
{
	Active = (Active == 0) ? 1 : 0;

	Opponent = (Active == 1) ? 0 : 1;
}

void TicTacToe::SetUpNextTurn()
{
	TogglePlayer();
	ToggleLetter();
}

void TicTacToe::PvERound()
{
	PrintBoard();

	Move player_move = Move();

	while (TakePlayerTurn(player_move) != TURN_END) {};

	if (m_State != RUNNING) return;

	else SetUpNextTurn();

	TakeAITurn(player_move);
}

void TicTacToe::PvPRound()
{
	PrintBoard();

	Move player_move = Move();

	while (TakePlayerTurn(player_move) != TURN_END) {};
}

void TicTacToe::TakeTurn()
{
	(this->*m_Gamemode)();
}

void TicTacToe::SetUpPvE()
{
	m_Gamemode = static_cast<Gamemode>(&TicTacToe::PvERound);

	Players[0] = HumanPlayer::CreatePlayer();

	Log("Choose Difficulty:\n1. Easy  2. Medium  3. Expert\n");
	int input;
	std::cin >> input;

	Difficulty chosen_difficulty = static_cast<Difficulty>(input);

	AI* bot = AI::CreatePlayer(chosen_difficulty);

	bot->SetValidMoves(s_Board.GetValidMoves(), s_Board.nr_of_available_moves);

	Players[1] = bot;
}

void TicTacToe::SetUpPvP()
{
	m_Gamemode = static_cast<Gamemode>(&TicTacToe::PvPRound);

	Players[0] = HumanPlayer::CreatePlayer();

	Players[1] = HumanPlayer::CreatePlayer();
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
	s_Board.Reset();

	Active = UNASSIGNED;

	ActiveLetter = UNOCCUPIED;

	m_State = RUNNING;
}



/*	LOGGING MEMBERS  */

void TicTacToe::PrintBoard() const
{
	s_Board.Print();
}

void TicTacToe::PrintDrawMessage() const
{
	Log("The game ended with no victor...\n");
}

void TicTacToe::PrintVictoryMessage() const
{
	const char* winner = Players[Active]->GetName();
	std::cout << "Congratulations, " << winner << "! You won!" << std::endl;
}

void TicTacToe::PrintWelcomeMessage() const
{
	Log("Let's play a game of Tic-Tac-Toe!\n");
}



/* INTERFACE */

void TicTacToe::End() const
{
	PrintBoard();

	if (m_State == DRAW) PrintDrawMessage();

	else PrintVictoryMessage();
}

void TicTacToe::Loop()
{
	while (m_State == RUNNING)
	{
		SetUpNextTurn();

		TakeTurn();
	}
}

TicTacToe& TicTacToe::Start()
{
	static TicTacToe tictactoe = TicTacToe();

	if (tictactoe.m_State != RUNNING) tictactoe.Reset();

	tictactoe.PrintWelcomeMessage();

	tictactoe.SetUpGame();

	return tictactoe;
}



/* DESTRUCTOR */

TicTacToe::~TicTacToe() {}