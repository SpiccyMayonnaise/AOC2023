#include <fstream>
#include <cstdint>
#include <string>
#include <iostream>

bool consumeString(const std::string& source, size_t& pos, const std::string& find) {
	bool found = source.substr(pos, find.length()) == find;

	if (found)
		pos = pos + find.length();

	return found;
}

auto isDigit(char c) {
	return c >= '0' && c <= '9';
};

std::tuple<bool, int32_t> consumeNumber(const std::string& source, size_t& pos) {
	bool found = false;

	int32_t num = -1;

	size_t i = 0;
	while (isDigit(source[pos + i])) {
		found = true;

		if (num == -1)
			num = 0;

		num = num*10 + source[pos+i]-'0';

		i++;
	}

	if (found)
		pos = pos + i;

	return {found, num};
}

constexpr uint32_t maxRed = 12, maxGreen = 13, maxBlue = 14;

int main() {
	std::ifstream inputStream{"./inputs/day2.txt", std::ios::in | std::ios::binary};

	uint32_t sum = 0;

	std::string line;
	while (std::getline(inputStream, line)) {
		size_t pos = 0;
		bool found;

		consumeString(line, pos, "Game ");
		auto [foundID, gameID] = consumeNumber(line, pos);
		consumeString(line, pos, ": ");

		uint32_t redCount = 0, greenCount = 0, blueCount = 0;

		bool inGame = true;
		while (inGame) {
			bool inSet = true;
			while (inSet) {
				auto [foundCount, count] = consumeNumber(line, pos);

				if (consumeString(line, pos, " red"))
					if (count > redCount) redCount = count;
				if (consumeString(line, pos, " green"))
					if (count > greenCount) greenCount = count;
				if (consumeString(line, pos, " blue"))
					if (count > blueCount) blueCount = count;

				inSet = consumeString(line, pos, ", ");
			}

			inGame = consumeString(line, pos, "; ");
		}

		bool valid = redCount <= maxRed && greenCount <= maxGreen && blueCount <= maxBlue;

		if (valid)
			sum += gameID;

		std::cout << "Game " << gameID << ": " << redCount << " red, " << greenCount << " green, " << blueCount << " blue. Decision: " << (valid ? "Valid" : "Invalid") << std::endl;
	}

	std::cout << "Sum: " << sum << std::endl;
}