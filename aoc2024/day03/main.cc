#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <regex>
#include <string>
#include <iostream>

void part1(std::ifstream& file);
void part2(std::ifstream& file);

int main() {
	std::ifstream file("../input.txt");
	if (!file.is_open()) {
		std::cerr << "Could not open file\n";
		return 1;
	}
	std::cout << "Part 1: ";
	part1(file);

	file.clear();
	file.seekg(0);

	std::cout << "Part 2: ";
	part2(file);
	
	file.close();
	return 0;
}

void part1(std::ifstream& file) {
	std::string line;
	long long grand_total {0};
	std::regex mul_pattern(R"(mul\((\d+),(\d+)\))");
	while (std::getline(file, line)) {
		std::smatch match;
		std::string search_str = line;

		while (std::regex_search(search_str, match, mul_pattern)) {
			int first = std::stoi(match[1]);
			int second = std::stoi(match[2]);
			grand_total += first * second;
			search_str = match.suffix();
		}
	}

	std::cout << grand_total << '\n';

}

void part2(std::ifstream& file) {
	std::string line;
	std::string content;

	while (std::getline(file, line)) {
		content += line + '\n';
	}

	bool enabled {true};
	long long grand_total {0};

	std::regex pattern(R"((?:do\(\)|don't\(\)|mul\((\d+),(\d+)\)))");

	std::smatch match;
	std::string search_str = content;

	while (std::regex_search(search_str, match, pattern)) {
		std::string instruction = match[0];
		if (instruction == "do()") {
			enabled = true;
		} else if (instruction == "don't()") {
			enabled = false;
		} else if (enabled && match[1].matched) {
			grand_total += std::stoi(match[1]) * std::stoi(match[2]);
		}
		search_str = match.suffix();
	}

	std::cout << grand_total << '\n';
}
