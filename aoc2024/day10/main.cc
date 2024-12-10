#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

void part1(std::ifstream& file);
void part2(std::ifstream& file);

const int dir_y[] = {0, 1, 0, -1};
const int dir_x[] = {-1, 0, 1, 0};

using Grid = std::vector<std::vector<int>>;

std::vector<std::vector<int>> read_input(std::ifstream& file) {
	std::vector<std::vector<int>> grid;
	std::string line;
	while (std::getline(file, line)) {
		std::vector<int> row;
		for (char c : line) {
			row.push_back(c - '0');
		}
		grid.push_back(row);
	}
	return grid;
}

bool is_valid(Grid& grid, std::size_t row, std::size_t col) {
	return row >= 0 && row < grid.size() && col >= 0 && col < grid[0].size();
}

int find_paths(Grid& grid, Grid& visited, std::set<std::pair<int, int>>& reachable_nines, int row, int col, int curr_height) {
	visited[row][col] = 1;
	int distinct_paths = 0;

	if (grid[row][col] == 9) {
		reachable_nines.insert({row, col});
		++distinct_paths;
	}

	for (int i = 0; i < 4; ++i) {
		int new_row {row + dir_y[i]};
		int new_col {col + dir_x[i]};

		if (is_valid(grid, new_row, new_col) && !visited[new_row][new_col]) {
			if (grid[new_row][new_col] == curr_height + 1) {
				distinct_paths += find_paths(grid, visited, reachable_nines, new_row, new_col, curr_height + 1);
			}
		}
	}
	visited[row][col] = 0;
	return distinct_paths;
}

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
	part2(file);
	
	file.close();
	return 0;
}

void part1(std::ifstream& file) {
	long total{0};
	Grid grid = read_input(file);
	for (int row = 0; row < static_cast<int>(grid.size()); ++row) {
		for (int col = 0; col < static_cast<int>(grid[0].size()); ++col) {
			if (grid[row][col] == 0) {
				Grid visited(grid.size(), std::vector<int>(grid[0].size(), 0));
				std::set<std::pair<int, int>> reachable_nines;
				find_paths(grid, visited, reachable_nines, row, col, 0);
				total += reachable_nines.size();
			}
		}
	}
	std::cout << total << '\n';
}

void part2(std::ifstream& file) {
	long long total{0};
	Grid grid = read_input(file);
	for (int row = 0; row < static_cast<int>(grid.size()); ++row) {
		for (int col = 0; col < static_cast<int>(grid[0].size()); ++col) {
			if (grid[row][col] == 0) {
				Grid visited(grid.size(), std::vector<int>(grid[0].size(), 0));
				std::set<std::pair<int, int>> reachable_nines;
				total += find_paths(grid, visited, reachable_nines, row, col, 0); 
			}
		}
	}
	std::cout << total << '\n';
}
