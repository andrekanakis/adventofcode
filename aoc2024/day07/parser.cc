#include "parser.h"
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

std::unordered_map<long long, std::vector<long long>> InputParser::parse_input(std::istream& input) {
	std::unordered_map<long long, std::vector<long long>> result;
	std::string line;

	while (std::getline(input, line)) {
	if (line.empty()) continue;

		auto colon_pos = line.find(':');
		if (colon_pos == std::string::npos) continue;
	

		long long key = std::stoll(line.substr(0, colon_pos));

		std::vector<long long> values;
		std::istringstream iss(line.substr(colon_pos + 1));
		std::string value_str;

		while(iss >> value_str) {
			values.push_back(std::stoll(value_str));
		}

		result[key] = values;
	}
	return result;
}
