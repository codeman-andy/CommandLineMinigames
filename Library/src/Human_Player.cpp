#include "Human_Player.h"

Human_Player* Human_Player::CreatePlayer()
{
	const char* name = GetPlayerNameFromInput();

	Human_Player* ptr = (Human_Player*) new Player(name);

	return ptr;
}