#include "TicTacToe.h"

int TicTacToe::board[3][3];
int TicTacToe::rows[3];
int TicTacToe::cols[3];
int TicTacToe::diagonals[2];
char TicTacToe::CharTranslation[3] = { '-', 'X', 'O' };
int (*TicTacToe::game_mode)();
Player* TicTacToe::current_player;
letter TicTacToe::current_letter;
Player* TicTacToe::Players[2];

TicTacToe::TicTacToe()
{
};

move* TicTacToe::GetValidMoves() {
	move valid_moves[9];
	int max_index = 0;

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (board[col][row] == UNOCCUPIED) {
				valid_moves[max_index] = move(col, row);
				max_index++;
			}
		}
	}

	move* r_valid_moves = (move*) new move[max_index];

	for (int index = 0; index < max_index; index++) {
		r_valid_moves[index] = valid_moves[index];
	}

	return r_valid_moves;
}

letter TicTacToe::GetCurrentLetter() {
	return current_letter;
}

int TicTacToe::CheckForDraw() {
	int letter_count = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; (j < 3) && (board[j][i] != UNOCCUPIED); j++) letter_count++;
	}

	if (letter_count >= 8) return DRAW;
}

int TicTacToe::CheckForWinner(int index, int CheckFor) {
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

int TicTacToe::UpdateAndCheckBoard(int x, int y) {
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

void TicTacToe::MarkOnBoard(int x, int y) {
	board[y][x] = current_letter;
}

int TicTacToe::MakeMove(int x, int y) {
	MarkOnBoard(x, y);

	if (UpdateAndCheckBoard(x, y) == WINNER_FOUND) {
		STATE = WINNER_FOUND;
		return WINNER_FOUND;
	}

	return RUNNING;
}

int TicTacToe::isPossible(int X, int Y) {
	if (board[Y][X] == UNOCCUPIED) return RUNNING;

	else Log("The coordinate you tried to mark is already occupied. Please, choose another.\n");
	return INVALID_MOVE;
}

int TicTacToe::isValid(int Coord) {
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
	move player_move = move();

	if (GetPlayerMove(player_move) == INVALID_COORDINATE) return INVALID_COORDINATE;

	else if (!isPossible(player_move.x, player_move.y)) return INVALID_MOVE;

	if (MakeMove(player_move.x, player_move.y) == WINNER_FOUND) return WINNER_FOUND;

	SetUpTurn();

	AI* bot = (AI*) current_player;

	bot->RemoveFromValidMoves(player_move);

	std::cout << "It's  " << bot->GetName() << "'s turn! ";

	move ai_move = bot->FindWinOrPreventLossOrMakeRandomMove(board, rows, cols, diagonals);

	std::cout << bot->GetName() << " chose [" << ai_move.x << ", " << ai_move.y << "]" << std::endl;

	if (MakeMove(ai_move.x, ai_move.y) == WINNER_FOUND) return WINNER_FOUND;

	bot->RemoveFromValidMoves(ai_move);

	SetUpTurn();

	return RUNNING;
}

int TicTacToe::PvPRound() {
	move player_move = move();

	if (GetPlayerMove(player_move) == INVALID_COORDINATE) return INVALID_COORDINATE;

	else if (!isPossible(player_move.x, player_move.y)) return INVALID_MOVE;

	if (MakeMove(player_move.x, player_move.y) == WINNER_FOUND) return WINNER_FOUND;

	SetUpTurn();

	PrintBoard();

	if (GetPlayerMove(player_move) == INVALID_COORDINATE) return INVALID_COORDINATE;

	else if (!isPossible(player_move.x, player_move.y)) return INVALID_MOVE;

	if (MakeMove(player_move.x, player_move.y) == WINNER_FOUND) return WINNER_FOUND;

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

	int board_dimensions[2] = { 3, 3 };
	bot_player->SetValidMoves(board_dimensions);
}

void TicTacToe::SetUpPvP() {
	game_mode = &PvPRound;
	Players[0] = Human_Player::CreatePlayer();
	Players[1] = Human_Player::CreatePlayer();
}

void TicTacToe::SetUpGame() {
	int input;

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

	for (int i = 0; i < 3; i++) {
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