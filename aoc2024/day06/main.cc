#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


void part1(std::ifstream& file);
void part2(std::ifstream& file);
void get_start(std::ifstream& file, std::vector<std::vector<char>>& grid, int& start_row, int& start_col);
char turn(char& dir);
bool guard_walk(std::vector<std::vector<char>>& grid, int& guard_row, int& guard_col, char& dir, bool& moved);


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
	
	int guard_row{};
	int guard_col{};
	char dir {'^'};
	bool moved {false};
	std::vector<std::vector<char>> grid;

	get_start(file, grid, guard_row, guard_col);

	// start walking, return true if we could walk
	// return false if guard exited
	bool still_in_area {true};
	while (still_in_area) {
		still_in_area = guard_walk(grid, guard_row, guard_col, dir, moved);

		if (moved) {
			++total;
		}
	}
	std::cout << total << '\n';
}

/*void part2(std::ifstream& file) {*/
/*	long long total{0};*/
/*	std::cout << total << '\n';*/
/*}*/

void get_start(std::ifstream& file, std::vector<std::vector<char>>& grid, int& start_row, int& start_col) {
	std::string line;

	while (std::getline(file, line)) {
		if (line.empty()) break;
		std::vector<char> row(line.begin(), line.end());
		grid.push_back(row);
	}

	int rows = static_cast<int>(grid.size());
	int cols = static_cast<int>(grid[0].size());

	// find the starting position for the guard
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			if (grid[r][c] == '^') {
				start_row = r;
				start_col = c;
			}
		}
	}
}

char turn(char& dir) {
	switch (dir) {
		case '^': return '>';
		case '>': return 'v';
		case 'v': return '<';
		case '<': return '^';
		default: return dir;
	}
}

bool guard_walk(std::vector<std::vector<char>>& grid, int& guard_row, int& guard_col, char& dir, bool& moved) {
	int next_row = guard_row;
	int next_col = guard_col;
	int row_dir {};
	int col_dir {};
	
	// get orientation (x, y), where X is hori and Y is vert.
	// (x,y) = (-1, 0) means we are going left, (0, 1) means we are going up
	switch (dir) {
		case '^': row_dir = -1; col_dir = 0; break; // up: decrease row
		case '>': row_dir = 0; col_dir = 1; break; // right: increase col
		case 'v': row_dir = 1; col_dir = 0; break; // down: increase row
		case '<': row_dir = 0; col_dir = -1; break; // left: decrease col
	}

	next_row += row_dir;
	next_col += col_dir;

	// check if we're leaving the area
	if (next_row < 0 || next_row >= static_cast<int>(grid.size()) ||
		next_col < 0 || next_col >= static_cast<int>(grid[0].size())) {
		return false;
	}

	// check if we have an obstacle infront
	if (grid[next_row][next_col] == '#') {
		dir = turn(dir);
		moved = false;
		return true;
	}

	// walk, mark as visited.
	guard_row = next_row;
	guard_col = next_col;
	if (grid[guard_row][guard_col] == '.') {
		moved = true;
		grid[guard_row][guard_col] = 'X';
	} else {
		moved = false;
	}
	return true;
}
