#include "BigNumbers.h"

int main() {
	BigInt test("500");
	BigInt test2("10000000000000000000000000000000000000000000000");

	std::cout << test << std::endl;
	std::cout << test2 << std::endl;
	std::cout << test - test2 << std::endl;

	int hold;
	std::cin >> hold;

	return 0;
}