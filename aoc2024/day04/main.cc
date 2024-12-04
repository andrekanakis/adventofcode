#include <algorithm>
#include <vector>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>

void part1(std::ifstream& file);
void part2(std::ifstream& file);
int countXMAS_part1(const std::string& str); 
std::vector<std::string> create_diagonals_tlbr(const std::vector<std::string>& input);
std::vector<std::string> create_diagonals_bltr(const std::vector<std::string>& input);
int countXMAS_part2(const std::vector<std::string>& input);


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
	std::vector<std::string> hor_input;
	std::vector<std::string> ver_input;
	const std::string target = "XMAS";

	std::string line;
	long long grand_total {0};

	while (std::getline(file, line)) {
		hor_input.push_back(line);
	}

	// Creating transposed vector
	for (size_t i = 0; i < hor_input.size(); ++i) {
		std::string transposed_string {};
		for (size_t j = 0; j < hor_input[i].size(); ++j) {
			transposed_string += hor_input[j][i];
		}
		ver_input.push_back(transposed_string);
	}

	// Search Horizontally
	for (size_t i = 0; i < hor_input.size(); ++i) {
		grand_total += countXMAS_part1(hor_input[i]); 
		std::string reversed_string = hor_input[i];
		std::reverse(reversed_string.begin(), reversed_string.end());
		grand_total += countXMAS_part1(reversed_string);
	}

	// Search vertically
	for (size_t i = 0; i < ver_input.size(); ++i) {
		grand_total += countXMAS_part1(ver_input[i]);
		std::string reversed_string = ver_input[i];
		std::reverse(reversed_string.begin(), reversed_string.end());
		grand_total += countXMAS_part1(reversed_string);
	}
	
	// Search horisontally top left -> bot right (+reverse)
	auto diagonals_tlbr = create_diagonals_tlbr(hor_input);
	for (const auto& diagonal : diagonals_tlbr) {
		grand_total += countXMAS_part1(diagonal);
		std::string reversed_diag = diagonal;
		std::reverse(reversed_diag.begin(), reversed_diag.end());
		grand_total += countXMAS_part1(reversed_diag);
	}

	// Search horisontally bot left -> top right (+reverse)
	auto diagonals_bltr = create_diagonals_bltr(hor_input);
	for (const auto& diagonal : diagonals_bltr) {
		grand_total += countXMAS_part1(diagonal);
		std::string reversed_diagonal = diagonal;
		std::reverse(reversed_diagonal.begin(), reversed_diagonal.end());
		grand_total += countXMAS_part1(reversed_diagonal);
	}
	
	std::cout << grand_total << '\n';

}

void part2(std::ifstream& file) {
	std::string line;
	std::vector<std::string> input;

	while (std::getline(file, line)) {
		input.push_back(line);
	}

	std::cout << countXMAS_part2(input) << '\n';
}

int countXMAS_part1(const std::string& str) {
	const std::string target = "XMAS";
	int count {0};
	size_t pos {0};

	while ((pos = str.find(target, pos)) != std::string::npos) {
		++count;
		pos += 1;
	}
	return count;
}

std::vector<std::string> create_diagonals_tlbr(const std::vector<std::string>& input) {
	std::vector<std::string> diagonals;
	int rows = input.size();
	int cols = input[0].size();

	// Diags from 1st row
	for (int start_col = 0; start_col <= cols - 4; ++start_col) {
		std::string diagonal;
		for (int i = 0, j = start_col; i < rows && j < cols; ++i, ++j) {
			diagonal += input[i][j];
		}
		if (diagonal.length() >= 4) {
			diagonals.push_back(diagonal);
		}
	}

	// Diags from 1st col, not 1st row
	for (int start_row = 1; start_row <= rows - 4; ++start_row) {
		std::string diagonal;
		for (int i = start_row, j = 0; i < rows && j < cols; ++i, ++j) {
			diagonal += input[i][j];
		}
		if (diagonal.length() >= 4) {
			diagonals.push_back(diagonal);
		}
	}
	return diagonals;
}

std::vector<std::string> create_diagonals_bltr(const std::vector<std::string>& input) {
	std::vector<std::string> diagonals;
	int rows = input.size();
	int cols = input[0].size();

	// Diags from 1st row
	for (int start_col = 0; start_col <= cols - 4; ++start_col) {
		std::string diagonal;
		for (int i = rows - 1 , j = start_col; i >= 0 && j < cols; --i, ++j) {
			diagonal += input[i][j];
		}
		if (diagonal.length() >= 4) {
			diagonals.push_back(diagonal);
		}
	}

	// Diags from 1st col, not 1st row
	for (int start_row = rows - 2; start_row >= 3; --start_row) {
		std::string diagonal;
		for (int i = start_row, j = 0; i >= 0 && j < cols; --i, ++j) {
			diagonal += input[i][j];
		}
		if (diagonal.length() >= 4) {
			diagonals.push_back(diagonal);
		}
	}
	return diagonals;
}

int countXMAS_part2(const std::vector<std::string>& input) {
	int count {0};
	int rows = input.size();
	int cols = input[0].size();

	for (int i = 1; i < rows -1; ++i) {
		for (int j = 1; j < cols - 1; ++j) {
			if (input[i][j] != 'A') {
				continue;
			}

			bool found = false;

			// check tlbr and bltr and check them with different combinations
			// of being reversed and not reversed
			if ((i > 0 && j > 0 && i < rows - 1 && j < cols - 1) &&
			input[i-1][j-1] == 'M' && input[i+1][j+1] == 'S' &&	// tlbr MAS
			input[i-1][j+1] == 'M' && input[i+1][j-1] == 'S') {	// bltr MAS
				found = true;
			}

			else if ((i > 0 && j > 0 && i < rows - 1 && j < cols - 1) &&
			input[i-1][j-1] == 'M' && input[i+1][j+1] == 'S' &&	// tlbr MAS
			input[i-1][j+1] == 'S' && input[i+1][j-1] == 'M') {	// bltr reversse MAS
				found = true;
			}

			else if ((i > 0 && j > 0 && i < rows - 1 && j < cols - 1) &&
			input[i-1][j-1] == 'S' && input[i+1][j+1] == 'M' &&	// tlbr reverse MAS
			input[i-1][j+1] == 'M' && input[i+1][j-1] == 'S') {	// bltr MAS
				found = true;
			}
			
			else if ((i > 0 && j > 0 && i < rows - 1 && j < cols - 1) &&
			input[i-1][j-1] == 'S' && input[i+1][j+1] == 'M' &&	// tlbr reverse MAS
			input[i-1][j+1] == 'S' && input[i+1][j-1] == 'M') {	// bltr reverse MAS
				found = true;
			}

			if (found) {
				++count;
			}

		}
	}
	return count;
}
