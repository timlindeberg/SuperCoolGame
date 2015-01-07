#include "Commandable.hpp"

namespace Lab3{

// Result

Commandable::Result::Result() :
	goForward(false),
	message("")
	{}

Commandable::Result::Result(const std::string& message, bool goForward) : 
	goForward(goForward),
	message(message)
	{}

bool Commandable::Result::HasMessage(){
	return message != "";
}

// Command

Commandable::Command::Command() {}

Commandable::Command::Command(CommandFunction f, bool movesGameForward) :
	f(f),
	movesGameForward(movesGameForward)
{}

// Commandable

Commandable::Commandable() : _commandMap(), _descriptionMap() { }


Commandable::Result Commandable::Command::operator()(const std::vector<std::string>& command) const{
	return f(command);
}

const Commandable::CommandMap& Commandable::GetCommandMap() const {
	return _commandMap;
}

bool Commandable::IsValidCommand(const std::string& command) const {
	return _commandMap.count(command);
}

Commandable::Result Commandable::Execute(const std::string& c,
 		std::vector<std::string>& words){
	if(IsValidCommand(c)){
		words.erase(words.begin());
		return _commandMap[c](words);
	}

	return Result();
}

const std::string& Commandable::CommandDescription(const std::string& command){
	return _descriptionMap[command];
}

}