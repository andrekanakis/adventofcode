#include <algorithm>
#include <utility>
#include <vector>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

void part1(std::ifstream& file);
void part2(std::ifstream& file);
std::string read_input(std::ifstream& file);
std::vector<std::string> change_to_zeros(std::string& input);
void sort_zeroes(std::vector<std::string>& input);
long long count_checksum(std::vector<std::string>& input);
void move_files(std::vector<std::string>& input);

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
	std::string part1_string = read_input(file);
	std::vector<std::string> vec_strings;
	vec_strings = change_to_zeros(part1_string);
	sort_zeroes(vec_strings);

	std::cout << count_checksum(vec_strings) << '\n';
}

void part2(std::ifstream& file) {
	std::string part2_string = read_input(file);
	std::vector<std::string> vec_strings = change_to_zeros(part2_string);
	move_files(vec_strings);
	std::cout << count_checksum(vec_strings) << '\n';
}

std::string read_input(std::ifstream& file) {
	std::string line;
	while (std::getline(file, line)) {
		return line;
	}
	return std::string {"0"};
}

std::vector<std::string> change_to_zeros(std::string& input) {
	int index {0};
	int id {0};
	std::vector<std::string> result;
	for (char c : input) {
		if (index % 2 == 0) {
			for (int i = 0; i < c - '0'; ++i) {
				std::string str = std::to_string(id);
				result.push_back(str);

			}
			++index;
			++id;
		} else if (index % 2 != 0) {
			for (int i = 0; i < c - '0'; ++i) {
				result.push_back(".");
			}
			++index;
		}
	}
	return result;
}

void sort_zeroes(std::vector<std::string>& input) {
	size_t left {0};
	size_t right {input.size() - 1};
	
	while (left < right) {
		while (left < right && input[left] != ".") {
			++left;
		}

		while (left < right && input[right] == ".") {
			--right;
		}

		if (left < right) {
			std::swap(input[left], input[right]);
			++left;
			--right;
		}
	}

	/*for (size_t i = 0; i < input.size(); ++i) {*/
	/*	if (input[i] == ".") {*/
	/*		for (size_t j = input.size() - 1; j > i; --j) {*/
	/*			if (input[j] != ".") {*/
	/*				std::swap(input[i], input[j]);*/
	/*				break;*/
	/*			}*/
	/*		}*/
	/*	}*/
	/*}*/
}

long long count_checksum(std::vector<std::string>& input) {
	long long total {0};
	for (size_t i = 0; i < input.size(); ++i) {
		if (input[i] == ".") {
			continue;
			/*return total;*/
		}	
		total += (std::stoi(input[i]) * i);
	}
	return total;
}

void move_files(std::vector<std::string>& input) {
	size_t pos {0};
	while (pos < input.size()) {

		while (pos < input.size() && input[pos] == ".") {
			++pos;
		}

		if (pos < input.size()) {
			std::string current = input[pos];
			size_t file_start {pos};
			size_t file_size {0};

			while (pos < input.size() && input[pos] == current) {
				++file_size;
				++pos;
			}

			size_t empty_count {0};
			size_t move_to {file_start};

			for (size_t i = 0; i < file_start; ++i) {
				if (input[i] == ".") {
					++empty_count;
					if (empty_count == file_size) {
						move_to = i - (file_size - 1);
						break;
					}
				} else {
					empty_count = 0;
				}
			}

			if (move_to < file_start) {
				for (size_t i = 0; i < file_size; ++i) {
					input[move_to + i] = current;
					input[file_start + i] = ".";
				}
			}
		}
	}
}
