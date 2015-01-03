#ifndef LAB3__PARSER
#define LAB3__PARSER

#include <string>
#include <vector>
#include <iostream>
#include "IO.hpp"

namespace Lab3{

struct Command{

	Command(const std::string& command, const std::string& object);

	std::string command;
	std::string object;
};

class Parser{

public:
	Parser();

	Command GetCommand() const;
};

}

#endif