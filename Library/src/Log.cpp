#include "Log.h"

void clear_buffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}

void ClearScreen()
{
	system("cls");
}

void Log(const char* const& message)
{
	std::cout << message;
}