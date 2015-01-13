#ifndef LAB3_COMMAND_EXECUTOR
#define LAB3_COMMAND_EXECUTOR

#include <iostream>
#include <initializer_list>
#include <string>
#include <vector>
#include <algorithm>

#include "Format.hpp"
#include "Commandable.hpp"

namespace Lab3{

class CommandExecutor {
public:

	CommandExecutor(State::Value state, Commandable* commandable);
	CommandExecutor(State::Value state, const std::initializer_list<Commandable*> commandables);

	void AddCommandable(Commandable* commandable);
	void SetState(State::Value state);
	bool Execute(std::vector<std::string>& command) const;
	bool TryCommands(Commandable* commandable, std::vector<std::string>& words,
 		/* out */ bool& goForward) const;

private:

	void PrintError(const std::string& command) const;
	void PrintHelp() const;

	State::Value _state;
	std::vector<Commandable*> _commandables;
};

}

#endif