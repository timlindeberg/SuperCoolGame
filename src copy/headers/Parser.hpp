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

	std::vector<std::string> ParseCommand();
	std::string MakeDelimiter(const std::string& c) const;

private:

	void PrintPreviousCommands();
	bool GetPreviousCommand(const std::string& command, std::vector<std::string>& outCommand);

	int EclidianMod(int a, int b) const;


	size_t _index;
	size_t _count;
	std::vector<std::vector<std::string>> _previousCommands;

	static const size_t NUM_PREVIOUS_COMMANDS;

};

}

#endif