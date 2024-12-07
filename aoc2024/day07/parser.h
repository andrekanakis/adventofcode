#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <unordered_map>

class InputParser {
public:
	static std::unordered_map<long long, std::vector<long long>> parse_input(std::istream& input);
};

#endif
