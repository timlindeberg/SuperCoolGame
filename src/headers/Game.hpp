#ifndef LAB3__GAME
#define LAB3__GAME

#include <fstream>
#include <map>
#include <utility>

#include "IO.hpp"
#include "Entity.hpp"
#include "Environment.hpp"
#include "Actor.hpp"
#include "Parser.hpp"

namespace Lab3{

class Game : public IO {
	
public:

	typedef bool (Game::*CommandFunction)(const std::string&);
	typedef std::map<std::string, CommandFunction> CommandMap;

	// Methods
	static Game* Get();
	
	Game();
	void Run();
	Actor* GetPlayer() const;
	bool IsRunning() const;

	// Commands

	bool SaveGame(const std::string& fileName);
	bool LoadGame(const std::string& fileName);
	bool Quit(const std::string& s);

protected:

	void SaveImplementation(std::ostream& os) const;
	void LoadImplementation(std::istream& is);

private:

	// Command map

	bool ValidCommand(const std::string& command);

	static const CommandMap _commandMap;
	static CommandMap MakeCommandMap();

	static const std::string _gameFilePath;
	static Game* _instance;
	bool _isRunning;
	std::vector<std::unique_ptr<Environment>> _environments;

	Actor* _player;

};
}

#endif