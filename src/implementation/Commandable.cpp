#include "Commandable.hpp"

namespace Lab3{

Commandable::Commandable() : _commandMap() { }

const Commandable::CommandMap& Commandable::GetCommandMap() const {
	return _commandMap;
}

bool Commandable::IsValidCommand(const std::string& command) const {
	return _commandMap.count(command);
}

}