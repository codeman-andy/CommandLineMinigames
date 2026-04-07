#include "TicTacToe.h"

#include "BoardTicTacToe.cpp"

TicTacToe::Board TicTacToe::board;
int (*TicTacToe::game_loop)();
Player* TicTacToe::current_player;
letter TicTacToe::current_letter;
Player* TicTacToe::Players[2];

TicTacToe::TicTacToe()
{
};

letter TicTacToe::GetCurrentLetter() {
	return current_letter;
}

int TicTacToe::CheckForDraw() {
	return (board.isFull());
}

void TicTacToe::MarkOnBoard(Board& board, const int& x, const int& y, const int& letter) {
	board.coordinates[y][x] = letter;
	board.row_counter[y] += 1;
	board.col_counter[x] += 1;

	if (x == y) board.diagonal_counter[0]++;

	if (x + y == 2) board.diagonal_counter[1]++;

	board.nr_of_available_moves--;
}

int TicTacToe::MakeMove(const move& move) {
	MarkOnBoard(board, move.x, move.y, current_letter);

	if (board.CheckState(move) == WINNER_FOUND) {
		STATE = WINNER_FOUND;
		return WINNER_FOUND;
	}

	return RUNNING;
}

int TicTacToe::isPossible(move& move) {
	if (board.coordinates[move.y][move.x] == UNOCCUPIED) return RUNNING;

	else Log("The coordinate you tried to mark is already occupied. Please, choose another.\n");
	return INVALID_MOVE;
}

int TicTacToe::isValid(const int& Coord) {
	if (Coord % 1 == 0 && Coord >= 0 && Coord <= 2) return RUNNING;

	else Log("Your last coordinate was invalid. Please, type your coordinates again.\n");
	return INVALID_COORDINATE;
}

int TicTacToe::GetPlayerMove(move& move) {
	Log("Where do you wish to place? (vertically)\n");
	std::cin >> move.y;
	if (!isValid(move.y)) return INVALID_COORDINATE;

	Log("Where do you wish to place? (horizontally)\n");
	std::cin >> move.x;
	if (!isValid(move.x)) return INVALID_COORDINATE;

	return RUNNING;
}

int TicTacToe::TakePlayerTurn(move& move) {

	if (GetPlayerMove(move) == INVALID_COORDINATE) return INVALID_COORDINATE;

	else if (!isPossible(move)) return INVALID_MOVE;

	if (MakeMove(move) == WINNER_FOUND) return WINNER_FOUND;

	return RUNNING;
}

int TicTacToe::TakeAITurn(const move& last_move) {
	AI* bot = (AI*) current_player;

	bot->RemoveFromValidMoves(last_move);

	std::cout << "It's  " << bot->GetName() << "'s turn! ";

	move ai_move = bot->MakeMove(board);

	std::cout << bot->GetName() << " chose [" << ai_move.x << ", " << ai_move.y << "]" << std::endl;

	if (MakeMove(ai_move) == WINNER_FOUND) return WINNER_FOUND;

	bot->RemoveFromValidMoves(ai_move);

	return RUNNING;
}

void TicTacToe::ToggleLetter() {
	current_letter = (current_letter == X) ? O : X;
}

void TicTacToe::TogglePlayer() {
	current_player = (current_player == Players[0]) ? Players[1] : Players[0];
}

void TicTacToe::SetUpNextTurn() {
	if (CheckForDraw()) {
		STATE = DRAW;
		return;
	}

	TogglePlayer();
	ToggleLetter();
}

int TicTacToe::PvERound() {
	PrintBoard();

	move player_move = move();

	int outcome = TakePlayerTurn(player_move);

	if (!outcome) return outcome;

	SetUpNextTurn();

	if (CheckForDraw()) {
		STATE = DRAW;
		return DRAW;
	}

	if (TakeAITurn(player_move) == WINNER_FOUND) return WINNER_FOUND;

	SetUpNextTurn();

	return RUNNING;
}

int TicTacToe::PvPRound() {
	PrintBoard();

	move player_move = move();

	int outcome = TakePlayerTurn(player_move);

	if (!outcome) return outcome;

	SetUpNextTurn();
	
	return RUNNING;
}

int TicTacToe::TakeTurn() {
	return game_loop();
}

void TicTacToe::SetUpPvE() {
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

void TicTacToe::SetUpPvP() {
	game_loop = &PvPRound;
	Players[0] = Human_Player::CreatePlayer();
	Players[1] = Human_Player::CreatePlayer();
}

void TicTacToe::SetUpGame() {
	Log("Select a match:\n1. Player vs. Player\n2. Player vs. AI\n");
	int input;
	std::cin >> input;

	if (input == PvP) SetUpPvP();

	else SetUpPvE();

	SetUpNextTurn();
}

void TicTacToe::Reset() {
	board.Reset();
	current_player = nullptr;
	current_letter = UNOCCUPIED;
}



/*	LOGGING MEMBERS  */

void TicTacToe::PrintBoard() {
	board.Print();
}

void TicTacToe::PrintDrawMessage() {
	Log("The game ended with no victor...\n");
}

void TicTacToe::PrintVictoryMessage() const {
	const char* winner = current_player->GetName();
	std::cout << "Congratulations, " << winner << "! You won!" << std::endl;
}

void TicTacToe::PrintWelcomeMessage() {
	Log("Let's play a game of Tic-Tac-Toe!");
}



/* INTERFACE */

void TicTacToe::End() const {
	TicTacToe::PrintBoard();

	if (STATE == DRAW) PrintDrawMessage();

	else PrintVictoryMessage();
}

void TicTacToe::Loop() {
	while (STATE == RUNNING) {
		TicTacToe::TakeTurn();
	}
}

TicTacToe& TicTacToe::Start() {
	STATE = RUNNING;

	if (board.isFull()) Reset();

	PrintWelcomeMessage();

	static TicTacToe game = TicTacToe();

	game.SetUpGame();

	return game;
}