#include "Player.h"

Player::Player() : m_name("Undefined") {};

Player::Player(const char* const& name) {
	m_name = name;
}

const char* Player::GetName() const {
	return m_name;
}

Player* Player::CreatePlayer(const char* name) {
	Player* ptr = new Player(name);

	return ptr;
}