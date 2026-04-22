#include "HumanPlayer.h"

HumanPlayer* HumanPlayer::CreatePlayer()
{
	const char* name = GetPlayerNameFromInput();

	return (HumanPlayer*) new Player(name);
}