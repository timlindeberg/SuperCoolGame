#ifndef LAB3__COMMANDABLE
#define LAB3__COMMANDABLE

#include <functional>
#include <vector>
#include <map>
#include <string>

#include "IO.hpp"
#include "GameStream.hpp" 	

#define ENTRY(type, name, func, state, desc) {										 \
		Command c(std::bind(&type::func, this, std::placeholders::_1), state, desc); \
		_commandMap[name].push_back(c);		 				 						 \
		}

namespace Lab3{

namespace State{
	enum Value {
		ALL 	= 0,
		INTRO 	= 1,
		NORMAL 	= 2,
		BATTLE 	= 3
	};	
}

class Commandable {	
public:

	struct Result {
		bool goForward;
		bool validCommand;

		Result();
		Result(bool goForward, bool validCommand);
	};

	class Command;
	typedef std::function<bool(const std::vector<std::string>&)> CommandFunction;
	typedef std::map<std::string, std::vector<Command>> CommandMap;

	class Command{
	public:

		Command(CommandFunction f, State::Value state, const std::string& description);

		bool operator()(const std::vector<std::string>& command) const;
		bool UsableInState(State::Value state) const;
		const std::string& Description() const;

	private:

		CommandFunction _f;
		State::Value _usableState;
		std::string _description;

	};

	Commandable();

	const CommandMap& GetCommandMap() const;
	bool IsValidCommand(const std::string& command) const;
	Result Execute(const std::string& command, std::vector<std::string>& words, State::Value currentState);

protected:

	CommandMap _commandMap;

private:
	virtual void InitCommandMap() = 0;

};
}

#endif