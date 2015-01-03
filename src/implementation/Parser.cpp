#include "Parser.hpp"

namespace Lab3{

Command::Command(const std::string& command, const std::string& object) :
	command(command),
	object(object)
{ }

Parser::Parser() {

}

Command Parser::GetCommand() const {
	static std::vector<std::string> validCommands {
		"go",
		"take",
		"help"
	};

	bool validCommand = false;
	std::string input;
	std::cin >> input;
	return Command("lol", "hej");
}

}