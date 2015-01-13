#include "Parser.hpp"

namespace Lab3{

const std::string Parser::ABOVE = "_";
const std::string Parser::BELOW = "‾";

Parser::Parser() : 
	_above(MakeDelimiter(ABOVE)),
	_below(MakeDelimiter(BELOW))
	{}

std::vector<std::string> Parser::ParseCommand() const {
	#define PRINT_STYLE(text) STYLE(COLOR(text, MAGENTA), BOLD)
	
	std::vector<std::string> words;
	while(words.size() == 0){
		std::string command;

		// Print input box
		Lab3::out << BeginBox(Format::MAGENTA);
		Lab3::out << std::endl;
		Lab3::out << EndBox();

		// Move input cursor
		Lab3::out << MoveCursor(-2, GameStream::INDENT_WIDTH + 1);
		std::getline(std::cin, command);
		Lab3::out << MoveCursor(1); // getline moves cursor by one
		Lab3::out << Clear();

		Utils::ToLowerCase(command);
		words = Utils::Split(command);
		Utils::RemoveBlankWords(words);
	}
	
	#undef PRINT_STYLE
	return words;
} 

std::string Parser::MakeDelimiter(const std::string& c) const {
	std::stringstream ss;
	for(size_t i = 0; i < Lab3::out.WIDTH; ++i){
		ss << c;
	}
	return ss.str();
}

}