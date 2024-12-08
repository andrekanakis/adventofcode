#ifndef PARSE_H
#define PARSE_H


#include <iostream>
#include <unordered_map>
#include <vector>

struct GridData {
	std::unordered_map<char, std::vector<std::pair<int, int>>> nodes;
	int rows;
	int cols;
};

class InputParser {
public:
	static GridData node_map(std::istream& input);
};

#endif
