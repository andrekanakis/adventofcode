#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>


bool is_decreasing(std::vector<int>& row);
bool is_increasing(std::vector<int>& row);
bool within_range(int x, int y);
void part1(std::ifstream& file);
void part2(std::ifstream& file);
bool is_valid(std::vector<int>);

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
	int safe_levels = 0;
	std::string line;
	while (std::getline(file, line)) {
		std::vector<int> numbers_on_line;
		std::istringstream iss(line);
		int num;

		while (iss >> num) {
			numbers_on_line.push_back(num);
		}
		
		if (is_decreasing(numbers_on_line) || is_increasing(numbers_on_line)) {
			safe_levels++;
		}

	}

	std::cout << safe_levels << '\n';
}

void part2(std::ifstream& file) {
	int safe_levels = 0;
	std::string line;
	while (std::getline(file, line)) {
		std::vector<int> numbers_on_line;
		std::istringstream iss(line);
		int num;
		while (iss >> num) {
			numbers_on_line.push_back(num);
		}
		
		if (is_valid(numbers_on_line)) safe_levels++;
	}

	std::cout << safe_levels << '\n';
}

bool within_range(int x, int y) {
	return ((std::abs(x-y) <= 3) && (std::abs(x-y) >= 1));
}

bool is_decreasing(std::vector<int>& row) {
	if (row.size() <= 1) return true;
	for (size_t i = 1; i < row.size(); ++i) {
		if (row[i] >= row[i-1] || !within_range(row[i], row[i-1])) return false;
	}
	return true;
}

bool is_increasing(std::vector<int>& row) {
	if (row.size() <= 1) return true;
	for (size_t i = 1; i < row.size(); ++i) {
		if (row[i] <= row[i-1] || !within_range(row[i], row[i-1])) return false;
	}
	return true;;
}

bool is_valid(std::vector<int> row) {
	if (is_increasing(row) || is_decreasing(row)) return true;

	for (size_t skip = 0; skip < row.size(); ++skip) {
		std::vector<int> temp;

		for (size_t i = 0; i < row.size(); ++i) {
			if (i != skip) {
				temp.push_back(row[i]);
			}
		}

		if (is_increasing(temp) || is_decreasing(temp)) return true;
	}

	return false;
}
