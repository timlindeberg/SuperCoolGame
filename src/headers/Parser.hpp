#ifndef LAB3_PARSER
#define LAB3_PARSER

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Format.hpp"
#include "Utils.hpp"
#include "GameStream.hpp"

namespace Lab3{

class Parser {
public:

	Parser();

	std::vector<std::string> ParseCommand() const;
	std::string MakeDelimiter(const std::string& c) const;

private:

	std::string _above;
	std::string _below;

	static const std::string ABOVE;
	static const std::string BELOW;
};

}

#endif