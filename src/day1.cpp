#include <iostream>
#include <fstream>
#include <cstdint>
#include "utils.h"

int main() {
	std::ifstream inputStream{"./inputs/day1.txt", std::ios::in | std::ios::binary};

	uint32_t sum = 0;

	std::string line;
	while (std::getline(inputStream, line)) {
		char firstDigit = '\0';
		char lastDigit = '\0';

		for (const char& c : line) {
			if (c >= '0' && c <= '9') {
				if (firstDigit == '\0')
					firstDigit = c;
				lastDigit = c;
			}
		}

		uint32_t num = (firstDigit - '0')*10 + lastDigit - '0';
		sum += num;

		std::cout << num << std::endl;
	}

	std::cout << sum << std::endl;

	return 0;
}