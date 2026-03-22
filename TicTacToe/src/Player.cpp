#include "Player.h"

Player::Player(const char* name) {
	m_name = name;
}

const char* Player::GetName() const {
	return m_name;
}