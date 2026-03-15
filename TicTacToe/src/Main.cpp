#include <iostream>

static void Log(const char* message) {
	std::cout << message << std::endl;
}

static void PrintBoard() {
	Log("  0 1 2");
	Log("  -----");
	for (unsigned char i = 0; i < 3; i++) {
		std::cout << +i;
		Log("|- - -|");
	}
	Log("  -----");
}


int main() {
	PrintBoard();
	std::cin.get();
}