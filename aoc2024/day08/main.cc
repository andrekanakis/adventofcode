#include "parse.h"
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <utility>
#include <unordered_map>

void part1(std::unordered_map<char, std::vector<std::pair<int, int>>> data, int rows, int cols);
void part2(std::unordered_map<char, std::vector<std::pair<int, int>>> data, int rows, int cols);

int main() {
	std::ifstream file("../input.txt");
	if (!file.is_open()) {
		std::cerr << "Could not open file\n";
		return 1;
	}

	auto [data, rows, cols] = InputParser::node_map(file);


	std::cout << "Part 1:\n";
	part1(data, rows, cols);

	file.clear();
	file.seekg(0);

	std::cout << "Part 2: \n";
	part2(data, rows, cols);
	
	file.close();
	return 0;
}

void part1(std::unordered_map<char, std::vector<std::pair<int, int>>> data, int rows, int cols) {
	std::set<std::pair<int, int>> antinodes;
	
	for (const auto& [key, positions] : data) {
		for (size_t i = 0; i < positions.size(); ++i) {
			for (size_t j = 0; j < positions.size(); ++j) {
				if (i == j) continue;
				int x1 = positions[i].first;
				int y1 = positions[i].second;
				int x2 = positions[j].first;
				int y2 = positions[j].second;

				int dx = x2 - x1;
				int dy = y2 - y1;

				std::pair<int, int> antinode1 = std::make_pair(x1 - dx, y1 - dy);
				std::pair<int, int> antinode2 = std::make_pair(x2 + dx, y2 + dy);

				if (0 <= antinode1.first && antinode1.first < rows
				&& 0 <= antinode1.second && antinode1.second < cols) {
					antinodes.insert(antinode1);
				}

				if (0 <= antinode2.first && antinode2.first < rows
				&& 0 <= antinode2.second && antinode2.second < cols) {
					antinodes.insert(antinode2);
				}

			}
		}
	}
	std::cout << antinodes.size() << '\n';
}

void part2(std::unordered_map<char, std::vector<std::pair<int, int>>> data, int rows, int cols) {
	std::set<std::pair<int, int>> antinodes;

	for (const auto& [key, positions] : data) {
		for (size_t i = 0; i < positions.size(); ++i) {
			for (size_t j = 0; j < positions.size(); ++j) {
				if (i == j) continue;
				int x1 = positions[i].first;
				int y1 = positions[i].second;
				int x2 = positions[j].first;
				int y2 = positions[j].second;

				int dx = x2 - x1;
				int dy = y2 - y1;

				for (int k = -rows; k < rows; ++k) {
					int kx = x1 + k * dx;
					int ky = y1 + k * dy;

					if (0 <= kx && kx < rows && 0 <= ky && ky < cols) {
						antinodes.insert(std::make_pair(kx, ky));
					}
				}
			}
		}
	}

	std::cout << antinodes.size() << '\n';
}
