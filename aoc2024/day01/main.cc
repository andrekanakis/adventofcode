#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

using std::vector;
using std::unordered_map;

int part1(std::ifstream& file);
int part2(std::ifstream& file);

int main() {

	std::ifstream file("../input.txt");
	if (!file.is_open()) {
		std::cerr << "Could not open file\n";
		return 1;
	}

	/*std::cout << part1(file) << '\n';*/
	std::cout << part2(file) << '\n';
	file.close();

	return 0;
}

int part1(std::ifstream& file) {
	vector<int> first_number;
	vector<int> second_number;

	int first;
	int second;
	while (file >> first >> second) {
		first_number.push_back(first);
		second_number.push_back(second);
	}

	std::sort(first_number.begin(), first_number.end());
	std::sort(second_number.begin(), second_number.end());

	int sum = 0;
	for (size_t i = 0; i < first_number.size(); ++i) {
		sum += std::abs(first_number[i] - second_number[i]);
	}

	return sum;
}

int part2(std::ifstream& file) {
	vector<int> lhs_numbers;
	unordered_map<int, int> rhs_numbers;

	int first;
	int second;
	while (file >> first >> second) {
		lhs_numbers.push_back(first);
		rhs_numbers[second]++;
	}

	int sum = 0;
	for (int lhs : lhs_numbers) {
		int matches = rhs_numbers[lhs];
		sum += lhs * matches;
	}

	return sum;
}
