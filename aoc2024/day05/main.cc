#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>

void part1(std::ifstream& file);
void part2(std::ifstream& file);
std::vector<std::vector<int>> process_vector(std::vector<std::vector<int>>& inputs, 
                                           const std::unordered_map<int, std::unordered_set<int>>& rules, bool is_part1);
std::pair<std::unordered_map<int, std::unordered_set<int>>, std::vector<std::vector<int>>> process_input(std::ifstream& file);

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
	long long total{0};
	auto [map_rules, all_numbers] = process_input(file);
	auto correct_vectors = process_vector(all_numbers, map_rules, true);
	for (const auto& vec : correct_vectors) {
		total += vec[vec.size()/2];
	}
	std::cout << total << '\n';
}

void part2(std::ifstream& file) {
	long long total{0};
	auto [map_rules, all_numbers] = process_input(file);

	auto correct_vectors = process_vector(all_numbers, map_rules, false);
	for (const auto& vec : correct_vectors) {
		total += vec[vec.size()/2];
	}


	std::cout << total << '\n';
}

std::pair<std::unordered_map<int, std::unordered_set<int>>, std::vector<std::vector<int>>> process_input(std::ifstream& file) {
	std::unordered_map<int, std::unordered_set<int>> map_rules;
	std::vector<std::vector<int>> all_numbers;
	std::string line;

	while (std::getline(file ,line)) {
		if (line.find('|') != std::string::npos) {
			size_t pos = line.find('|');
			int first = std::stoi(line.substr(0, pos));
			int second = std::stoi(line.substr(pos + 1));
			map_rules[first].insert(second);
		} else if (!line.empty()) {
			std::vector<int> numbers;
			std::stringstream ss(line);
			std::string number;
			while (std::getline(ss, number, ',')) {
				numbers.push_back(std::stoi(number));
			}
			all_numbers.push_back(numbers);
		}
	}

	return {map_rules, all_numbers}; 
}

std::vector<std::vector<int>> process_vector(std::vector<std::vector<int>>& input,
					     const std::unordered_map<int, std::unordered_set<int>>& rules,
					     bool is_part1) {
	std::vector<std::vector<int>> result_vectors;

	for (auto numbers : input) {
		bool needs_change {false};

		for (size_t i = 0; i < numbers.size(); ++i) {
			if (auto it = rules.find(numbers[i]); it != rules.end()) {
				for (int value : it->second) {
					for (size_t j = 0; j < i; ++j) {
						if (numbers[j] == value) {
							needs_change = true;
							break;
						}
					}
					if (needs_change) break;
				}
			}
			if (needs_change) break;
		}

		if ((!needs_change && is_part1) || (needs_change && !is_part1)) {
			if (is_part1) {
				result_vectors.push_back(numbers);
			} else {
				bool made_changes;
				do {
					made_changes = false;
					for (size_t i = 0; i < numbers.size(); ++i) {
						if (auto it = rules.find(numbers[i]); it != rules.end()) {
							for (int value : it->second) {
								for (size_t j = i + 1; j < numbers.size(); ++j) {
									if (numbers[j] == value) {
										std::swap(numbers[i], numbers[j]);
										made_changes = true;
										break;
									}
								}
							}
						}
					}
				} while (made_changes);
				result_vectors.push_back(numbers);
			}
		}
	}
	return result_vectors;
}
