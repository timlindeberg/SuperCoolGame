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

	Game();
	
	static Game* Instance();

	void Run();
	Actor* GetPlayer() const;
	Room* GetCurrentRoom() const;
	bool IsRunning() const;

	// Commands
	Result SaveGame(const std::vector<std::string>& command);
	Result LoadGame(const std::vector<std::string>& command);
	Result Quit(const std::vector<std::string>& command);
	Result Help(const std::vector<std::string>& command);
	Result Inspect(const std::vector<std::string>& command);

protected:

	void SaveImplementation(std::ostream& os) const;
	void LoadImplementation(std::istream& is);

private:

	bool TryCommands(Commandable* commandable,
	 	std::vector<std::string>& words, bool& goForward);

	virtual void InitCommandMap() override;

	// Command map
	std::vector<std::string> ParseCommand() const;

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