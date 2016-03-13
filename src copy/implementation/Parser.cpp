#include "Parser.hpp"

namespace Lab3{

const size_t Parser::NUM_PREVIOUS_COMMANDS = 3;

Parser::Parser() : 
	_index(0),
	_count(0),
	_previousCommands(NUM_PREVIOUS_COMMANDS)
	{}

std::vector<std::string> Parser::ParseCommand() {
	std::vector<std::string> words;
	while(words.size() == 0){
		std::string command;

		// Print input box
		Lab3::out << BeginBox(Format::MAGENTA);
		if(_count != 0){
			PrintPreviousCommands();
		}
		Lab3::out << std::endl;
		Lab3::out << EndBox();

		// Move input cursor
		Lab3::out << MoveCursor(-2, GameStream::OUTER_INDENT_WIDTH + GameStream::INDENT_WIDTH + 1);
		std::getline(std::cin, command);
		Lab3::out << MoveCursor(1); // getline moves cursor by one
		Lab3::out << Clear();
		if(GetPreviousCommand(command, words)){
			return words;
		}
		
		Utils::ToLowerCase(command);
		words = Utils::Split(command);
		Utils::RemoveBlankWords(words);
	}
	_previousCommands[_index] = words;
	_index = (_index + 1) % NUM_PREVIOUS_COMMANDS;
	if(_count < NUM_PREVIOUS_COMMANDS)
	 	++_count;
	
	return words;
} 

bool Parser::GetPreviousCommand(const std::string& command, std::vector<std::string>& outCommand){
	try{
		size_t i = std::stoi(command);
		if(i >= 1 && i <= _count){
			int index = EclidianMod(_index - i, NUM_PREVIOUS_COMMANDS);
			outCommand = _previousCommands[index];
			return true;
		}
	}catch(std::invalid_argument& e){
		return false;
	}
	return false;
}

void Parser::PrintPreviousCommands(){
	for(size_t i = 0; i < _count; ++i){
		int index = EclidianMod(_index - i - 1, NUM_PREVIOUS_COMMANDS);
		Lab3::out << COLOR((i + 1), MAGENTA) << ": " << Utils::Concatenate(_previousCommands[index]);
		Lab3::out << std::endl;
	}
	Lab3::out << Delimiter();
}

int Parser::EclidianMod(int a, int b) const{
	int r = a % b;
  	return r >= 0 ? r : r + std::abs(b);
}

}