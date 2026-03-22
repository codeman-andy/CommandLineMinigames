#include "TicTacToe.h"

TicTacToe::TicTacToe()
	: board({ UNOCCUPIED }), rows({ EMPTY }), cols({ EMPTY }), diagonals({ EMPTY }), CharTranslation('-', 'X', 'O'), current_letter(UNOCCUPIED), Players({ nullptr }), current_player(nullptr), game_state(RUNNING)
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

int TicTacToe::MakeMove(size_t X, size_t Y) {
	MarkOnBoard(X, Y);

	if (UpdateBoard(X, Y) == WINNER_FOUND) {
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

int TicTacToe::isValid(size_t coord) {
	if (coord % 1 == 0 && coord >= 0 && coord <= 2) return RUNNING;

	else Log("Your last coordinate was invalid. Please, type your coordinates again.\n");
	return INVALID_COORDINATE;
}

int TicTacToe::GetMove(size_t& X, size_t& Y) {
	Log("Where do you wish to place? (vertically)\n");
	std::cin >> Y;
	if (!isValid(Y)) return INVALID_COORDINATE;

	Log("Where do you wish to place? (horizontally)\n");
	std::cin >> X;
	if (!isValid(X)) return INVALID_COORDINATE;

	return RUNNING;
}

int TicTacToe::TakeTurn() {
	size_t X = 0;
	size_t Y = 0;

	if (!GetMove(X, Y)) return INVALID_COORDINATE;

	if (!isPossible(X, Y)) return INVALID_MOVE;

	if (!MakeMove(X, Y)) return WINNER_FOUND;

	return RUNNING;
}

void TicTacToe::SetLetter() {
	if (current_letter == X) current_letter = O;
	else current_letter = X;
}

void TicTacToe::SetPlayer() {
	if (current_player == Players[0]) current_player = Players[1];
	else current_player = Players[0];
}

void TicTacToe::SetUpTurn() {
	SetPlayer();
	SetLetter();
}

void TicTacToe::SetUpPlayers() {
	Players[0] = Player::CreatePlayer();
	Players[1] = Player::CreatePlayer();
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