#include <tuple>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

auto isDigit(char c) {
	return c >= '0' && c <= '9';
};

std::tuple<bool, int32_t, size_t> nextNumber(const std::string& source, size_t& pos) {
	bool found = false;

	int32_t num = -1;

	size_t i = 0;
	while ((pos + i) < source.length()) {
		if (isDigit(source[pos + i]))
			break;

		i++;
	}

	auto startPos = pos + i;

	while ((pos + i) < source.length()) {
		if (!isDigit(source[pos + i]))
			break;

		found = true;

		if (num == -1)
			num = 0;

		num = num*10 + source[pos+i]-'0';

		i++;
	}

	pos = pos + i;

	return {found, num, startPos};
}

struct PartNumber {
	size_t xPos;
	size_t yPos;
	size_t length;
	int32_t value;
};

bool isSymbol(char c) {
	return !isDigit(c) && (c != '.') && (c != '\n') && (c != '\r');
}

bool checkPosition(size_t xPos, size_t yPos, const std::vector<std::string>& lines) {
	bool result = false;

	if (xPos > 0) {
		result |= isSymbol(lines[yPos][xPos - 1]);
		if (yPos > 0)
			result |= isSymbol(lines[yPos - 1][xPos - 1]);
		if (yPos < lines.size() - 1)
			result |= isSymbol(lines[yPos + 1][xPos - 1]);
	}

	if (yPos > 0)
		result |= isSymbol(lines[yPos - 1][xPos]);
	if (yPos < lines.size() - 1)
		result |= isSymbol(lines[yPos + 1][xPos]);


	if (xPos < lines[0].length() - 1) {
		result |= isSymbol(lines[yPos][xPos + 1]);
		if (yPos > 0)
			result |= isSymbol(lines[yPos - 1][xPos + 1]);
		if (yPos < lines.size() - 1)
			result |= isSymbol(lines[yPos + 1][xPos + 1]);
	}

	return result;
}

bool isPartNumber(PartNumber partNumber, const std::vector<std::string>& lines) {
	for (size_t i = 0; i < partNumber.length; ++i) {
		if (checkPosition(partNumber.xPos + i, partNumber.yPos, lines))
			return true;
	}

	return false;
}

int main() {
	std::ifstream inputStream{"./inputs/day3.txt", std::ios::in | std::ios::binary};

	std::vector<PartNumber> partNumbers;
	std::vector<std::string> lines;

	size_t lineNumber = 0;
	std::string line;
	while (std::getline(inputStream, line)) {
		lines.push_back(line);

		size_t pos = 0;

		bool foundNumber = true;
		while (foundNumber) {
			auto [found, value, startPos] = nextNumber(line, pos);
			foundNumber = found;

			if (found)
				partNumbers.push_back({.xPos = startPos, .yPos = lineNumber, .length = pos - startPos, .value = value});
		}

		lineNumber++;
	}

	int32_t sum = 0;

	for (auto partNumber : partNumbers) {
		bool valid = isPartNumber(partNumber, lines);

		std::cout << partNumber.value << ": " << valid << std::endl;

		if (valid)
			sum += partNumber.value;
	}

	std::cout << sum << std::endl;
}