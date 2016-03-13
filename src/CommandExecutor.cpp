#include "CommandExecutor.hpp"

namespace Lab3{

CommandExecutor::CommandExecutor(State::Value state, Commandable* commandable) : _state(state) {
	_commandables.push_back(commandable);
}

CommandExecutor::CommandExecutor(State::Value state, 
	const std::initializer_list<Commandable*> commandables) :
	_state(state),
	_commandables(commandables.size())
{
	std::copy(commandables.begin(), commandables.end(), _commandables.begin());
}

void CommandExecutor::AddCommandable(Commandable* commandable){
	_commandables.push_back(commandable);
}

void CommandExecutor::SetState(State::Value state){
	_state = state;
}

bool CommandExecutor::Execute(std::vector<std::string>& command) const {
	bool goForward = false;
	bool success = false;
	if(command[0] == "help"){
		PrintHelp();
		return false;
	}
	for(Commandable* commandable : _commandables){
		success = TryCommands(commandable, command, /* out */ goForward);
		if(success){
			break;
		}
	}

	if(!success){
		PrintError(command[0]);
	}
	return goForward;
}

bool CommandExecutor::TryCommands(Commandable* commandable, std::vector<std::string>& words,
 		/* out */ bool& goForward) const {
	std::string command = words[0];
	Commandable::Result result = commandable->Execute(command, words, _state);
	goForward = result.goForward;
	return result.validCommand;
}

void CommandExecutor::PrintError(const std::string& command) const {
	Lab3::out << BeginBox(GameStream::FAIL_COLOR);
	Lab3::out << COLOR(command, RED) << " is not a valid command! Type " <<
	COLOR("help", YELLOW) << " to see a list of valid commands." << std::endl;
	Lab3::out << EndBox();
}

void CommandExecutor::PrintHelp() const {
	std::map<std::string, bool> printed;

	Lab3::out << BeginBox(GameStream::SUCCESS_COLOR);
	Lab3::out << Alignment::CENTER << "The following commands can currently be used" << std::endl;
	Lab3::out << Delimiter();
	std::vector<std::string> commandStrings;
	for(Commandable* commandable : _commandables){
		for(auto iter : commandable->GetCommandMap()){
			std::vector<Commandable::Command> commands = iter.second;
			for(Commandable::Command& command : commands){
				if(command.UsableInState(_state)){
					std::string desc = command.Description();
					if(printed[desc]){
						continue;
					}
					std::stringstream ss;
					ss << COLOR(iter.first, YELLOW) << " - ";
					ss << desc;
					commandStrings.push_back(ss.str());
					printed[desc] = true;
					break;
				} 
			}
		}
	}

	std::sort(commandStrings.begin(), commandStrings.end());
	for(auto& s : commandStrings)
		Lab3::out << s << std::endl;

	Lab3::out << EndBox();
}

}
