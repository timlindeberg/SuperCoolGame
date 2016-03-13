#include "Commandable.hpp"

namespace Lab3{

// Result

Commandable::Result::Result() :
	goForward(false),
	validCommand(false)
	{}

Commandable::Result::Result(bool validCommand, bool goForward) : 
	goForward(goForward),
	validCommand(validCommand)
	{}

// Command

Commandable::Command::Command(CommandFunction f, State::Value state, const std::string& description) :
	_f(f),
	_usableState(state),
	_description(description)
{}

bool Commandable::Command::UsableInState(State::Value state) const {
	return _usableState == State::ALL || _usableState == state;
}

const std::string& Commandable::Command::Description() const {
	return _description;
}

// Commandable

Commandable::Commandable() : _commandMap() { }


bool Commandable::Command::operator()(const std::vector<std::string>& command) const{
	return _f(command);
}

const Commandable::CommandMap& Commandable::GetCommandMap() const {
	return _commandMap;
}

bool Commandable::IsValidCommand(const std::string& command) const {
	return _commandMap.count(command);
}

Commandable::Result Commandable::Execute(const std::string& commandName,
 		std::vector<std::string>& words, State::Value currentState){
	Result r;
	if(IsValidCommand(commandName)){
		r.validCommand = true;
		bool success = false;
		for(Command command : _commandMap[commandName]){
			if(command.UsableInState(currentState)){
				success = true;
				words.erase(words.begin());
				r.goForward = command(words);
				break;
			}
		}
		if(!success){
			Lab3::out << BeginBox(GameStream::FAIL_COLOR);
			Lab3::out << "The command " << COLOR(commandName, YELLOW) << " is not usable right now." << std::endl;
			Lab3::out << EndBox();
		}
	}

	return r;
}
}