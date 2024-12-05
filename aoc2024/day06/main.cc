#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>

void part1(std::ifstream& file);
void part2(std::ifstream& file);

int main() {
	std::ifstream file("../input.txt");
	if (!file.is_open()) {
		std::cerr << "Could not open file\n";
		return 1;
	}

	std::cout << "Part 1:\n";
	part1(file);

	file.clear();
	file.seekg(0);

	std::cout << "Part 2: \n";
	/*part2(file);*/
	
	file.close();
	return 0;
}

void part1(std::ifstream& file) {
	long long total{0};
	std::cout << total << '\n';
}

void part2(std::ifstream& file) {
	long long total{0};
	std::cout << total << '\n';
}
