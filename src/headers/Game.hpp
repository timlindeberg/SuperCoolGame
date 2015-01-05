#ifndef LAB3__GAME
#define LAB3__GAME

#include <fstream>
#include <map>
#include <utility>
#include <algorithm>
#include <string>

#include "IO.hpp"
#include "Commandable.hpp"
#include "Item.hpp"
#include "Room.hpp"
#include "Actor.hpp"

namespace Lab3{

class Game : public IO, public Commandable {
	
public:
	typedef std::function<bool(const std::vector<std::string>&)> CommandFunction;
	typedef std::map<std::string, CommandFunction> CommandMap;

	Game();
	
	static Game* Instance();

	void Run();
	Actor* GetPlayer() const;
	Room* GetCurrentRoom() const;
	bool IsRunning() const;

	// Commands
	bool SaveGame(const std::vector<std::string>& command);
	bool LoadGame(const std::vector<std::string>& command);
	bool Quit(const std::vector<std::string>& command);
	bool Help(const std::vector<std::string>& command);

protected:

	void SaveImplementation(std::ostream& os) const;
	void LoadImplementation(std::istream& is);

private:

	virtual void InitCommandMap() override;

	// Command map
	std::vector<std::string> ParseCommand() const;
	bool IsValidCommand(const std::string& command) const;
	bool Execute(Commandable* commandable, const std::string& c, std::vector<std::string>& command);

	static const std::string _gameFilePath;
	static const std::string _savePath;
	static Game* _instance;

	bool _isRunning;
	std::vector<std::unique_ptr<Room>> _rooms;
	Actor* _player;
	Room* _currentRoom;

};
}

#endif