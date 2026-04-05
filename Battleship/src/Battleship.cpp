#include "BoardBattleship.cpp"

Battleship::Board Battleship::board;
char Battleship::CharTranslation[3] = { '-', 'X', 'O' };
int (*Battleship::game_loop)();
Player* Battleship::current_player;
Player* Battleship::Players[2];


Battleship::Battleship()
{
};

move* Battleship::GetValidMoves(const Board& board) {
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

int Battleship::CheckForWinner(const Board& board, const int& index, const int& CheckFor) {
	if (CheckFor == CheckForRow) {
		if (board.coordinates[index][0] == board.coordinates[index][1] && board.coordinates[index][0] == board.coordinates[index][2]) return WINNER_FOUND;
	}
	if (CheckFor == CheckForCol) {
		if (board.coordinates[0][index] == board.coordinates[1][index] && board.coordinates[0][index] == board.coordinates[2][index]) return WINNER_FOUND;
	}

	return RUNNING;
}

int Battleship::CheckBoard(const Board& board, const int& x, const int& y) {
	if (board.row_counter[y] == FULL && CheckForWinner(board, y, CheckForRow) == WINNER_FOUND) return WINNER_FOUND;
	if (board.col_counter[x] == FULL && CheckForWinner(board, x, CheckForCol) == WINNER_FOUND) return WINNER_FOUND;

	return RUNNING;
}

void Battleship::MarkOnBoard(Board& board, const int& x, const int& y) {
	board.coordinates[y][x] = X;
	board.row_counter[y] += 1;
	board.col_counter[x] += 1;

	board.nr_of_available_moves--;
}

int Battleship::MakeMove(const int& x, const int& y) {
	MarkOnBoard(board, x, y);

	if (CheckBoard(board, x, y) == WINNER_FOUND) {
		STATE = WINNER_FOUND;
		return WINNER_FOUND;
	}

	return RUNNING;
}

int Battleship::isPossible(const int& X, const int& Y) {
	if (board.coordinates[Y][X] == UNOCCUPIED) return RUNNING;

	else Log("The coordinate you tried to mark is already occupied. Please, choose another.\n");
	return INVALID_MOVE;
}

int Battleship::isValid(const int& Coord) {
	if (Coord % 1 == 0 && Coord >= 0 && Coord <= 9) return RUNNING;

	else Log("Your last coordinate was invalid. Please, type your coordinates again.\n");
	return INVALID_COORDINATE;
}

int Battleship::GetPlayerMove(move& move) {
	Log("Where do you wish to place? (vertically)\n");
	std::cin >> move.y;
	if (!isValid(move.y)) return INVALID_COORDINATE;

	Log("Where do you wish to place? (horizontally)\n");
	std::cin >> move.x;
	if (!isValid(move.x)) return INVALID_COORDINATE;

	return RUNNING;
}

int Battleship::TakePlayerTurn(move& move) {

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

void Battleship::TogglePlayer() {
	current_player = (current_player == Players[0]) ? Players[1] : Players[0];
}

void Battleship::SetUpNextTurn() {
	TogglePlayer();
}

int Battleship::PvERound() {
	PrintBoard();

	move player_move = move();

	int outcome = TakePlayerTurn(player_move);

	if (!outcome) return outcome;

	SetUpNextTurn();

	if (TakeAITurn(player_move) == WINNER_FOUND) return WINNER_FOUND;

	SetUpNextTurn();

	return RUNNING;
}

int Battleship::PvPRound() {
	PrintBoard();

	move player_move = move();

	int outcome = TakePlayerTurn(player_move);

	if (!outcome) return outcome;

	SetUpNextTurn();

	return RUNNING;
}

int Battleship::TakeTurn() {
	return game_loop();
}

void Battleship::SetUpPvE() {
	game_loop = &PvERound;

	Players[0] = Human_Player::CreatePlayer();

	Log("Choose Difficulty:\n1. Easy  2. Medium  3. Expert\n");
	int input;
	std::cin >> input;

	difficulty chosen_difficulty = static_cast<difficulty>(input);

	const char* name = (chosen_difficulty == EASY) ? "Pam" : (chosen_difficulty == MEDIUM) ? "Donald J. Trump" : "Peter Thiel";

	AI* bot_player = AI::CreatePlayer(name, chosen_difficulty);

	bot_player->SetValidMoves(GetValidMoves(board), board.nr_of_available_moves);

	Players[1] = bot_player;
}

void Battleship::SetUpPvP() {
	game_loop = &PvPRound;
	Players[0] = Human_Player::CreatePlayer();
	Players[1] = Human_Player::CreatePlayer();
}

void Battleship::SetUpGame() {
	Log("Select a match:\n1. Player vs. Player\n2. Player vs. AI\n");
	int input;
	std::cin >> input;

	if (input == PvP) SetUpPvP();

	else SetUpPvE();

	SetUpNextTurn();
}



/*	LOGGING MEMBERS  */

void Battleship::PrintBoard() {
	Log("  A B C D E F G H I J K\n");
	Log("  ---------------------\n");

	for (int i = 1; i < 10; i++) {
		std::cout << i << "|" << CharTranslation[board.coordinates[i][0]] << " " << CharTranslation[board.coordinates[i][1]] << " " << CharTranslation[board.coordinates[i][2]] << "|" << std::endl;
	}

	Log("  ---------------------\n");
}

void Battleship::PrintVictoryMessage() const {
	const char* winner = current_player->GetName();
	std::cout << "Congratulations, " << winner << "! You won!" << std::endl;
}

void Battleship::PrintWelcomeMessage() {
	Log("Let's play a game of Tic-Tac-Toe!");
}