#include <iostream>
#include <fstream>
#include <cstdint>
#include <array>
#include <string>

uint32_t findFirstDigit(const std::string& source, bool forwards) {
	std::array<std::string, 9> digits = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
	std::array<std::string, 9> words = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

	size_t bestIndex = std::string::npos;
	uint32_t bestDigit = 0;

	for (size_t i = 0; i < digits.size(); ++i) {
		auto pos = forwards ? source.find(digits[i]) : source.rfind(digits[i]);

		if (pos != std::string::npos) {
			if (bestIndex == std::string::npos) {
				bestIndex = pos;
				bestDigit = i;
			}

			if ((forwards && pos < bestIndex) || (!forwards && pos > bestIndex)) {
				bestIndex = pos;
				bestDigit = i;
			}
		}
	}
	for (size_t i = 0; i < words.size(); ++i) {
		auto pos = forwards ? source.find(words[i]) : source.rfind(words[i]);

		if (pos != std::string::npos) {
			if (!forwards)
				pos += words[i].length() - 1;

			if (bestIndex == std::string::npos) {
				bestIndex = pos;
				bestDigit = i;
			}

			if ((forwards && pos < bestIndex) || (!forwards && pos > bestIndex)) {
				bestIndex = pos;
				bestDigit = i;
			}
		}
	}

	if (bestIndex == std::string::npos)
		return 0;

	return bestDigit + 1;
}

int main() {
	std::ifstream inputStream{"./inputs/day1.txt", std::ios::in | std::ios::binary};

	uint32_t sum = 0;

	std::string line;
	while (std::getline(inputStream, line)) {
		auto firstDigit = findFirstDigit(line, true);
		auto lastDigit = findFirstDigit(line, false);

		auto num = firstDigit * 10 + lastDigit;
		std::cout << num << std::endl;

		sum += num;
	}

	std::cout << sum << std::endl;

	return 0;
}