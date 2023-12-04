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
	int32_t xPos;
	int32_t yPos;
	int32_t length;
	int32_t value;
};

struct Gear {
	size_t numPartNumbers = 0;
	int32_t gearRatio = 0;
};

bool isSymbol(char c) {
	return !isDigit(c) && (c != '.') && (c != '\n') && (c != '\r');
}

void addGear(const PartNumber& partNumber, Gear& gear) {
	gear.numPartNumbers++;

	if (gear.numPartNumbers > 2)
		return;

	if (gear.gearRatio == 0)
		gear.gearRatio = partNumber.value;
	else
		gear.gearRatio *= partNumber.value;
}

bool checkPosition(int32_t xPos, int32_t yPos, const std::vector<std::string>& lines, const PartNumber& partNumber, std::vector<std::vector<Gear>>& gears) {
	bool result = false;

	if (xPos >= 0 && xPos < lines[0].length()) {
		result |= isSymbol(lines[yPos][xPos]);

		if (lines[yPos][xPos] == '*')
			addGear(partNumber, gears[yPos][xPos]);

		if (yPos > 0) {
			result |= isSymbol(lines[yPos - 1][xPos]);

			if (lines[yPos - 1][xPos] == '*')
				addGear(partNumber, gears[yPos - 1][xPos]);
		}
		if (yPos < lines.size() - 1) {
			result |= isSymbol(lines[yPos + 1][xPos]);

			if (lines[yPos + 1][xPos] == '*')
				addGear(partNumber, gears[yPos + 1][xPos]);
		}
	}

	return result;
}

bool isPartNumber(const PartNumber& partNumber, const std::vector<std::string>& lines, std::vector<std::vector<Gear>>& gears) {
	for (int32_t i = -1; i <= partNumber.length; ++i) {
		if (checkPosition(partNumber.xPos + i, partNumber.yPos, lines, partNumber, gears))
			return true;
	}

	return false;
}

int main() {
	std::ifstream inputStream{"./inputs/day3.txt", std::ios::in | std::ios::binary};

	std::vector<PartNumber> partNumbers;
	std::vector<std::string> lines;
	std::vector<std::vector<Gear>> gears;

	size_t lineNumber = 0;
	std::string line;
	while (std::getline(inputStream, line)) {
		lines.push_back(line);
		gears.emplace_back(line.length());

		size_t pos = 0;

		bool foundNumber = true;
		while (foundNumber) {
			auto [found, value, startPos] = nextNumber(line, pos);
			foundNumber = found;

			if (found)
				partNumbers.push_back({.xPos = static_cast<int32_t>(startPos), .yPos = static_cast<int32_t>(lineNumber), .length = static_cast<int32_t>(pos - startPos), .value = value});
		}

		lineNumber++;
	}

	int32_t sum = 0;

	for (auto partNumber : partNumbers) {
		bool valid = isPartNumber(partNumber, lines, gears);

		std::cout << partNumber.value << ": " << valid << std::endl;

		if (valid)
			sum += partNumber.value;
	}

	int32_t gearRatioSum = 0;

	for (auto gearVector : gears) {
		for (auto gear : gearVector) {
			if (gear.numPartNumbers == 2)
				gearRatioSum += gear.gearRatio;
		}
	}

	std::cout << sum << std::endl;
	std::cout << gearRatioSum << std::endl;
}