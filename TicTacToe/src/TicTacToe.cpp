#include "TicTacToe.h"

size_t TicTacToe::board[3][3];
size_t TicTacToe::rows[3];
size_t TicTacToe::cols[3];
size_t TicTacToe::diagonals[2];
char TicTacToe::CharTranslation[3] = { '-', 'X', 'O' };
int (*TicTacToe::game_mode)();
Player* TicTacToe::current_player;
letter TicTacToe::current_letter;
Player* TicTacToe::Players[2];

TicTacToe::TicTacToe()
{
};

letter TicTacToe::GetCurrentLetter() {
	return current_letter;
}

int TicTacToe::CheckForWinner(size_t index, size_t CheckFor) {
	if (CheckFor == CheckForRow) {
		if (board[index][0] == board[index][1] && board[index][0] == board[index][2]) return WINNER_FOUND;
	}
	if (CheckFor == CheckForCol) {
		if (board[0][index] == board[1][index] && board[0][index] == board[2][index]) return WINNER_FOUND;
	}
	if (CheckFor == CheckForDiagLeft) {
		if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) return WINNER_FOUND;
	}
	if (CheckFor == CheckForDiagRight) {
		if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) return WINNER_FOUND;
	}

	return RUNNING;
}

int TicTacToe::UpdateAndCheckBoard(size_t x, size_t y) {
	rows[y] += 1;
	cols[x] += 1;
	if (rows[y] == FULL && CheckForWinner(y, CheckForRow) == WINNER_FOUND) return WINNER_FOUND;
	if (cols[x] == FULL && CheckForWinner(x, CheckForCol) == WINNER_FOUND) return WINNER_FOUND;

	if (x == y) diagonals[0]++;
	if (x + y == 2) diagonals[1]++;
	if (diagonals[0] == FULL && CheckForWinner(0, CheckForDiagLeft) == WINNER_FOUND) return WINNER_FOUND;
	if (diagonals[1] == FULL && CheckForWinner(1, CheckForDiagRight) == WINNER_FOUND) return WINNER_FOUND;

	return RUNNING;
}

void TicTacToe::MarkOnBoard(size_t x, size_t y) {
	board[y][x] = current_letter;
}

int TicTacToe::MakeMove(size_t x, size_t y) {
	MarkOnBoard(x, y);

	if (UpdateAndCheckBoard(x, y) == WINNER_FOUND) {
		STATE = WINNER_FOUND;
		return WINNER_FOUND;
	}

	return RUNNING;
}

int TicTacToe::isPossible(size_t X, size_t Y) {
	if (board[Y][X] == UNOCCUPIED) return RUNNING;

	else Log("The coordinate you tried to mark is already occupied. Please, choose another.\n");
	return INVALID_MOVE;
}

int TicTacToe::isValid(size_t Coord) {
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

/*
int TicTacToe::TakePlayerTurn() {
	move move = { 0 };

	if (GetPlayerMove(move) == INVALID_COORDINATE) return INVALID_COORDINATE;

	else if (!isPossible(move.x, move.y)) return INVALID_MOVE;

	if (MakeMove(move.x, move.y) == WINNER_FOUND) return WINNER_FOUND;

	return RUNNING;
}

int TicTacToe::TakeAITurn() {
	Log("It is Pam's turn!\n");
	AI* bot = (AI*) current_player;
	move decision = bot->MakeRandomMove();
	if (MakeMove(decision.x, decision.y) == WINNER_FOUND) return WINNER_FOUND;

	return RUNNING;
}
*/

void TicTacToe::ToggleLetter() {
	current_letter = (current_letter == X) ? O : X;
}

void TicTacToe::TogglePlayer() {
	current_player = (current_player == Players[0]) ? Players[1] : Players[0];
}

/*
void TicTacToe::ToggleTurn() {
	current_turn = (current_turn == turns[0]) ? turns[1] : turns[0];
}
*/

void TicTacToe::SetUpTurn() {
	TogglePlayer();
	ToggleLetter();
}

int TicTacToe::PvERound() {
	move move = { 0 };

	if (GetPlayerMove(move) == INVALID_COORDINATE) return INVALID_COORDINATE;

	else if (!isPossible(move.x, move.y)) return INVALID_MOVE;

	if (MakeMove(move.x, move.y) == WINNER_FOUND) return WINNER_FOUND;

	SetUpTurn();

	AI* bot = (AI*) current_player;

	bot->RemoveFromValidMoves(move);

	std::cout << "It's  " << bot->GetName() << "'s turn! ";

	move = bot->WinOrMakeRandomMove(board, rows, cols, diagonals);

	std::cout << bot->GetName() << " chose [" << move.x << ", " << move.y << "]" << std::endl;

	if (MakeMove(move.x, move.y) == WINNER_FOUND) return WINNER_FOUND;

	bot->RemoveFromValidMoves(move);

	SetUpTurn();

	return RUNNING;
}

int TicTacToe::PvPRound() {
	move move = { 0 };

	if (GetPlayerMove(move) == INVALID_COORDINATE) return INVALID_COORDINATE;

	else if (!isPossible(move.x, move.y)) return INVALID_MOVE;

	if (MakeMove(move.x, move.y) == WINNER_FOUND) return WINNER_FOUND;

	SetUpTurn();

	PrintBoard();

	if (GetPlayerMove(move) == INVALID_COORDINATE) return INVALID_COORDINATE;

	else if (!isPossible(move.x, move.y)) return INVALID_MOVE;

	if (MakeMove(move.x, move.y) == WINNER_FOUND) return WINNER_FOUND;

	SetUpTurn();

	return RUNNING;
}

int TicTacToe::TakeTurn() {
	return game_mode();
}

void TicTacToe::SetUpPvE() {
	game_mode = &PvERound;

	Players[0] = Human_Player::CreatePlayer();

	AI* bot_player = AI::CreatePlayer("Pam");

	Players[1] = bot_player;

	size_t board_dimensions[2] = { 3, 3 };
	bot_player->SetValidMoves(board_dimensions);
}

void TicTacToe::SetUpPvP() {
	game_mode = &PvPRound;
	Players[0] = Human_Player::CreatePlayer();
	Players[1] = Human_Player::CreatePlayer();
}

void TicTacToe::SetUpGame() {
	size_t input;

	Log("Select a match:\n1. Player vs. Player\n2. Player vs. AI\n");
	std::cin >> input;

	if (input == 1) SetUpPvP();

	else SetUpPvE();

	SetUpTurn();
}



/*	LOGGING MEMBERS  */

void TicTacToe::PrintBoard() {
	Log("  0 1 2\n");
	Log("  -----\n");

	for (size_t i = 0; i < 3; i++) {
		std::cout << +i << "|" << CharTranslation[board[i][0]] << " " << CharTranslation[board[i][1]] << " " << CharTranslation[board[i][2]] << "|" << std::endl;
	}

	Log("  -----\n");
}

void TicTacToe::PrintVictoryMessage() {
	const char* winner = current_player->GetName();
	std::cout << "Congratulations, " << winner << "! You won!" << std::endl;
}

void TicTacToe::PrintWelcomeMessage() {
	Log("Let's play a game of Tic-Tac-Toe!");
}