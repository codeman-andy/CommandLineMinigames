#include "Player.h"

Player::Player() : m_name("Undefined") {}

Player::Player(const char* const& name)
{
	m_name = name;
}

const char* Player::GetName() const
{
	return m_name;
}

const char* Player::GetPlayerNameFromInput()
{
	clear_buffer();

	Log("What do you want to be called? (max. 32-characters)\n");
	char input[32];
	std::cin >> input;

	size_t name_length = strlen(input);

	char* name = (char*)malloc(name_length + 1);
	for (int i = 0; i <= name_length; i++)
	{
		name[i] = input[i];
	}

	return name;
}

Player* Player::CreatePlayer(const char* name)
{
	return new Player(name);
}