#pragma once

#include "Player/Factory.h"

#include "Player/Human.h"


class HumanPlayerFactory : PlayerFactory {
public:
	Player* CreatePlayer() override
	{
		const char* name = GetPlayerNameFromInput();

		return new HumanPlayer(name);
	}

	/* Destructor */
	~HumanPlayerFactory() {}

private:
	const char* GetPlayerNameFromInput()
	{
		Log("\nWhat do you want to be called? (max. 32-characters)\n");
		std::string input;
		std::getline(std::cin, input);

		size_t name_length = input.length();

		char* name = (char*) malloc(name_length + 1);
		for (int i = 0; i <= name_length; i++)
		{
			name[i] = input[i];
		}

		return name;
	}
};