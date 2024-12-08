#include "parse.h"
#include <string>
#include <utility>
#include <vector>


GridData InputParser::node_map(std::istream &input) {
	std::unordered_map<char, std::vector<std::pair<int, int>>> result;
	std::string line;
	std::vector<std::vector<char>> grid;

	while (std::getline(input, line)) {
		if (line.empty()) continue;
		std::vector<char> row(line.begin(), line.end());
		grid.push_back(row);
	}

	int rows = static_cast<int>(grid.size());
	int cols = static_cast<int>(grid[0].size());
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			if (grid[r][c] != '.') {
				char my_char = grid[r][c];
				result[my_char].push_back(std::make_pair(r, c));
				/*result.insert({my_char, std::make_pair(r, c)});*/
			}
		}
	}

	return {result, rows, cols};
}
