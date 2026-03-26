#include "AI.h"

AI::AI(const char* name) {
	m_name = name;
	m_valid_moves = nullptr;
	m_nr_of_valid_moves = 1;
}

void AI::SetValidMoves(size_t dimensions_lengths[]) {
	for (size_t i = 0; i < 2; i++) {
		m_nr_of_valid_moves = m_nr_of_valid_moves * dimensions_lengths[i];
	}

	m_valid_moves = (move*) calloc(m_nr_of_valid_moves, sizeof(coords));

	size_t idx = 0;
	for (size_t i = 0; i < dimensions_lengths[0]; i++) {
		for (size_t j = 0; j < dimensions_lengths[1]; j++) {
			m_valid_moves[idx].position.y = i;
			m_valid_moves[idx].position.x = j;
			m_valid_moves[idx].valid = true;
			idx++;
		}
	}
}

void AI::RemoveValidMove(coords move) {
	m_nr_of_valid_moves--;

	size_t i;
	while (m_valid_moves[i].position.x != move.x && m_valid_moves[i].position.y != move.y) {
		i++;
	}

	while (i < m_nr_of_valid_moves) {
		m_valid_moves[i].position = m_valid_moves[i + 1].position;
	}
}

coords AI::MakeRandomMove() {
	size_t random_index = rand() % (m_nr_of_valid_moves - 1);
	return m_valid_moves[random_index].position;
}

coords AI::DecideMove(size_t board[3][3], size_t rows[3], size_t cols[3], size_t diagonals[2], letter my_letter) {
	coords decision = { 0 };
	size_t win_c = 0;
	for (int i = 0; (i < 3 && rows[i] < FULL); i++) {
		if (my_letter * rows[i] == board[i][0] + board[i][1] + board[i][2]) {
			if (my_letter * rows[i] > win_c) {
				size_t k = 0;
				while (board[i][k] != UNOCCUPIED) k++;
				decision.x = k;
				decision.y = i;
				win_c = my_letter * rows[i];
			}
		}
	}
	for (int j = 0; (j < 3 && cols[j] < FULL); j++) {
		if (my_letter * cols[j] == board[0][j] + board[1][j] + board[2][j]) {
			if (my_letter * cols[j] > win_c) {
				size_t m = 0;
				while (board[m][j] != UNOCCUPIED) m++;
				decision.x = j;
				decision.y = m;
				win_c = my_letter * cols[j];
			}
		}
	}
	std::cout << "Pam decided: [" << decision.y << ", " << decision.x << "]" << std::endl;
	return decision;
}