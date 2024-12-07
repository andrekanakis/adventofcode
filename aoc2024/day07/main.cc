#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "parser.h"

void part1(std::unordered_map<long long, std::vector<long long>> data);
void part2(std::unordered_map<long long, std::vector<long long>> data);
bool try_to_sum(long long target, const std::vector<long long>& nums, size_t index, long long current, bool part2);
long long concat(long long a, long long b);

int main() {
	std::ifstream file("../input.txt");
	if (!file.is_open()) {
		std::cerr << "Could not open file\n";
		return 1;
	}

	auto data = InputParser::parse_input(file);

	std::cout << "Part 1:\n";
	part1(data);

	file.clear();
	file.seekg(0);

	std::cout << "Part 2: \n";
	part2(data);
	
	file.close();
	return 0;
}
void part1(std::unordered_map<long long, std::vector<long long>> data) {
	long long total{0};

	for (const auto& [key, values] : data) {
		if (!values.empty()) {
			if (try_to_sum(key, values, 1, values[0], false)) {
				total += key;
			}
		}
	}

	std::cout << total << '\n';
}


void part2(std::unordered_map<long long, std::vector<long long>> data) {
	long long total{0};

	for (const auto& [key, values] : data) {
		if (try_to_sum(key, values, 1, values[0], true)) {
			total += key;
		}
	}
	std::cout << total << '\n';
}

bool try_to_sum(long long target, const std::vector<long long>& nums, size_t index, long long current, bool part2) {
	if (index == nums.size()) {
		return current == target;
	}

	if (try_to_sum(target, nums, index + 1, current + nums[index], part2)) {
		return true;
	}

	if (try_to_sum(target, nums, index + 1, current * nums[index], part2)) {
		return true;
	}

	if (part2) {
		if (try_to_sum(target, nums, index + 1, concat(current, nums[index]), part2)) {
			return true;
		}
	}

	return false;
}

long long concat(long long a, long long b) {
	std::string str_a {std::to_string(a)};
	std::string str_b {std::to_string(b)};

	return std::stoll(str_a + str_b);
}
