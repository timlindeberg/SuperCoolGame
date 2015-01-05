#ifndef LAB3__COMMANDABLE
#define LAB3__COMMANDABLE

#include <functional>
#include <vector>
#include <map>
#include <string>

#include "IO.hpp"

namespace Lab3{

class Commandable{
public:
	typedef std::function<bool(const std::vector<std::string>&)> CommandFunction;
	typedef std::map<std::string, CommandFunction> CommandMap;

	Commandable();

	const CommandMap& GetCommandMap() const;
	bool IsValidCommand(const std::string& command) const;


protected:

	CommandMap _commandMap;

private:
	virtual void InitCommandMap() = 0;

};
}

#endif