#include "Human_Player.h"

const char* Human_Player::GetPlayerNameFromInput() {
	clear_buffer();
	Log("What do you want to be called? (max. 32-characters)\n");
	char input[32];
	std::cin >> input;
	size_t name_length = strlen(input);
	char* name = (char*)malloc(name_length + 1);
	for (int i = 0; i <= name_length; i++) {
		name[i] = input[i];
	}
	return name;
}

Human_Player* Human_Player::CreatePlayer() {
	const char* name = GetPlayerNameFromInput();

	Human_Player* ptr = (Human_Player*) new Player(name);

	return ptr;
}