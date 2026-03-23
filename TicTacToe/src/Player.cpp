#include "Player.h"

Player::Player(const char* name) {
	m_name = name;
}

const char* Player::GetName() const {
	return m_name;
}

Player* Player::CreatePlayer(const char* name) {
	Player* ptr = new Player(name);

	return ptr;
}