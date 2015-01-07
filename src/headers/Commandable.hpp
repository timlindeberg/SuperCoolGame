#ifndef LAB3__COMMANDABLE
#define LAB3__COMMANDABLE

#include <functional>
#include <vector>
#include <map>
#include <string>

#include "IO.hpp"

#define ENTRY(type, name, func, description) { 						\
		_commandMap[name] = Command( 				 			 	\
			std::bind(&type::func, this, std::placeholders::_1), 	\
			false); 									 		 	\
		_descriptionMap[name] = description;					 	\
	}

namespace Lab3{

enum State {
	NORMAL 	= 0,
	BATTLE 	= 1,
	TRADE 	= 2
};

class Commandable {	
public:

	struct Result {
		bool goForward;
		std::string message;

		Result();
		Result(const std::string& message, bool goForward);

		bool HasMessage();
	};

	struct Command;
	typedef std::function<Result(const std::vector<std::string>&)> CommandFunction;
	typedef std::map<std::string, Command> CommandMap;
	typedef std::map<std::string, std::string> DescriptionMap;

	struct Command{
		CommandFunction f;
		bool movesGameForward;

		Command();
		Command(CommandFunction f, bool movesGameForward);

		Result operator()(const std::vector<std::string>& command) const;

	};

	Commandable();

	const CommandMap& GetCommandMap() const;
	bool IsValidCommand(const std::string& command) const;
	Result Execute(const std::string& c, std::vector<std::string>& command);
	const std::string& CommandDescription(const std::string& command);

protected:

	

	CommandMap _commandMap;
	DescriptionMap _descriptionMap;

private:
	virtual void InitCommandMap() = 0;

};
}

#endif