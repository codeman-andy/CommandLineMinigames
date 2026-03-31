#include "TicTacToe.h"

ttt_board TicTacToe::board;
int TicTacToe::rows[3];
int TicTacToe::cols[3];
int TicTacToe::diagonals[2];
char TicTacToe::CharTranslation[3] = { '-', 'X', 'O' };
int (*TicTacToe::game_loop)();
Player* TicTacToe::current_player;
letter TicTacToe::current_letter;
Player* TicTacToe::Players[2];

TicTacToe::TicTacToe()
{
};

int TicTacToe::GetNrOfValidMoves(int board[3][3]) {
	int nr_of_valid_moves = 0;

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (board[col][row] == UNOCCUPIED) nr_of_valid_moves++;
		}
	}

	return nr_of_valid_moves;
}

move* TicTacToe::GetValidMoves(ttt_board board) {
	move* valid_moves = (move*) new move[board.nr_of_available_moves];

	int index = 0;
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (board.coordinates[row][col] == UNOCCUPIED) {
				valid_moves[index] = move(col, row);
				index++;
			}
		}
	}

	return valid_moves;
}

letter TicTacToe::GetCurrentLetter() {
	return current_letter;
}

int TicTacToe::CheckForDraw() {
	int letter_count = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; (j < 3) && (board.coordinates[j][i] != UNOCCUPIED); j++) letter_count++;
	}

	if (letter_count >= 8) return DRAW;
}

int TicTacToe::CheckForWinner(ttt_board board, int index, int CheckFor) {
	if (CheckFor == CheckForRow) {
		if (board.coordinates[index][0] == board.coordinates[index][1] && board.coordinates[index][0] == board.coordinates[index][2]) return WINNER_FOUND;
	}
	if (CheckFor == CheckForCol) {
		if (board.coordinates[0][index] == board.coordinates[1][index] && board.coordinates[0][index] == board.coordinates[2][index]) return WINNER_FOUND;
	}
	if (CheckFor == CheckForDiagLeft) {
		if (board.coordinates[0][0] == board.coordinates[1][1] && board.coordinates[0][0] == board.coordinates[2][2]) return WINNER_FOUND;
	}
	if (CheckFor == CheckForDiagRight) {
		if (board.coordinates[0][2] == board.coordinates[1][1] && board.coordinates[0][2] == board.coordinates[2][0]) return WINNER_FOUND;
	}

	return RUNNING;
}

int TicTacToe::CheckBoard(ttt_board board, int x, int y) {
	if (board.row_counter[y] == FULL && CheckForWinner(board, y, CheckForRow) == WINNER_FOUND) return WINNER_FOUND;
	if (board.col_counter[x] == FULL && CheckForWinner(board, x, CheckForCol) == WINNER_FOUND) return WINNER_FOUND;

	if (board.diagonal_counter[0] == FULL && CheckForWinner(board, 0, CheckForDiagLeft) == WINNER_FOUND) return WINNER_FOUND;
	if (board.diagonal_counter[1] == FULL && CheckForWinner(board, 1, CheckForDiagRight) == WINNER_FOUND) return WINNER_FOUND;

	return RUNNING;
}

void TicTacToe::MarkOnBoard(ttt_board& board, int x, int y, int letter) {
	board.coordinates[y][x] = letter;
	board.row_counter[y] += 1;
	board.col_counter[x] += 1;

	if (x == y) board.diagonal_counter[0]++;

	if (x + y == 2) board.diagonal_counter[1]++;

	board.nr_of_available_moves--;
}

int TicTacToe::MakeMove(int x, int y) {
	MarkOnBoard(board, x, y, current_letter);

	if (CheckBoard(board, x, y) == WINNER_FOUND) {
		STATE = WINNER_FOUND;
		return WINNER_FOUND;
	}

	return RUNNING;
}

int TicTacToe::isPossible(int X, int Y) {
	if (board.coordinates[Y][X] == UNOCCUPIED) return RUNNING;

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

	move ai_move = bot->MakeMove(board);

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
	return game_loop();
}

void TicTacToe::SetUpPvE() {
	game_loop = &PvERound;

	Log("Choose Difficulty:\n1. Easy  2. Medium  3. Expert\n");
	int input;
	std::cin >> input;

	difficulty chosen_difficulty = static_cast<difficulty>(input);

	Players[0] = Human_Player::CreatePlayer();

	const char* name = (chosen_difficulty == EASY) ? "Pam" : (chosen_difficulty == MEDIUM) ? "Donald J. Trump" : "Peter Thiel";

	AI* bot_player = AI::CreatePlayer(name, chosen_difficulty);

	Players[1] = bot_player;

	move* valid_moves = GetValidMoves(board);
	bot_player->SetValidMoves(valid_moves, board.nr_of_available_moves);
}

void TicTacToe::SetUpPvP() {
	game_loop = &PvPRound;
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
		std::cout << i << "|" << CharTranslation[board.coordinates[i][0]] << " " << CharTranslation[board.coordinates[i][1]] << " " << CharTranslation[board.coordinates[i][2]] << "|" << std::endl;
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