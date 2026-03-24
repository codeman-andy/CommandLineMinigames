#include "TicTacToe.h"

size_t TicTacToe::board[3][3];
size_t TicTacToe::rows[3];
size_t TicTacToe::cols[3];
size_t TicTacToe::diagonals[2];
int (*TicTacToe::current_turn)();
Player* TicTacToe::current_player;
letter TicTacToe::current_letter;
char TicTacToe::CharTranslation[3] = { '-', 'X', 'O' };

TicTacToe::TicTacToe()
	: turns({ nullptr }), Players({ nullptr })
{
};

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

int TicTacToe::UpdateBoard(size_t x, size_t y) {
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

	if (UpdateBoard(x, y) == WINNER_FOUND) {
		game_state = WINNER_FOUND;
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

int TicTacToe::GetPlayerMove(size_t& X, size_t& Y) {
	Log("Where do you wish to place? (vertically)\n");
	std::cin >> Y;
	if (!isValid(Y)) return INVALID_COORDINATE;

	Log("Where do you wish to place? (horizontally)\n");
	std::cin >> X;
	if (!isValid(X)) return INVALID_COORDINATE;

	return RUNNING;
}

int TicTacToe::TakePlayerTurn() {
	size_t X = 0;
	size_t Y = 0;

	if (GetPlayerMove(X, Y) == INVALID_COORDINATE) return INVALID_COORDINATE;

	else if (!isPossible(X, Y)) return INVALID_MOVE;

	if (MakeMove(X, Y) == WINNER_FOUND) return WINNER_FOUND;

	return RUNNING;
}

int TicTacToe::TakeAITurn() {
	Log("It is Pam's turn!");
	coords decision = AI::DecideMove();
	if (MakeMove(decision.x, decision.y) == WINNER_FOUND) return WINNER_FOUND;

	return RUNNING;
}

int TicTacToe::TakeTurn() {
	return current_turn();
}

void TicTacToe::ToggleLetter() {
	current_letter = (current_letter == X) ? O : X;
}

void TicTacToe::TogglePlayer() {
	current_player = (current_player == Players[0]) ? Players[1] : Players[0];
}

void TicTacToe::ToggleTurn() {
	current_turn = (current_turn == turns[0]) ? turns[1] : turns[0];
}

void TicTacToe::SetUpTurn() {
	ToggleTurn();
	TogglePlayer();
	ToggleLetter();
}

void TicTacToe::SetUpPvE() {
	Players[0] = Human_Player::CreatePlayer();
	Players[1] = (AI*) Player::CreatePlayer("Pam");
}

void TicTacToe::SetUpPvP() {
	Players[0] = Human_Player::CreatePlayer();
	Players[1] = Human_Player::CreatePlayer();
}

void TicTacToe::SetUpGame() {
	Log("Select a match:\n1. Player vs. Player\n2. Player vs. AI\n");
	size_t input;
	std::cin >> input;
	if (input == 1) {
		turns[0] = { &TakePlayerTurn };
		turns[1] = { &TakePlayerTurn };
		SetUpPvP();
	}
	else {
		turns[0] = { &TakePlayerTurn };
		turns[1] = { &TakeAITurn };
	}
}

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