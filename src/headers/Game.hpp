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
#include "Actor.hpp"
#include "GameStream.hpp"
#include "Parser.hpp"
#include "CommandExecutor.hpp"

namespace Lab3{

class Player;
class Room;
class Game : public IO, public Commandable {
	
public:

	Game();
	static Game* Instance();

	void Run();
	Player* GetPlayer() const;
	State::Value State() const;
	Room* GetCurrentRoom() const;
	bool IsRunning() const;

	// Commands
	bool NewGame(const std::vector<std::string>& command);
	bool SaveGame(const std::vector<std::string>& command);
	bool LoadGame(const std::vector<std::string>& command);
	bool Quit(const std::vector<std::string>& command);

protected:

	void SaveImplementation(std::ostream& os) const;
	void LoadImplementation(std::istream& is);

private:

	void Introduction();
	virtual void InitCommandMap() override;

	static const std::string _gameFilePath;
	static const std::string _savePath;
	static const std::string _saveExtension;
	static Game* _instance;

	State::Value _currentState;
	bool _isRunning;
	std::vector<std::unique_ptr<Room>> _rooms;
	Player* _player;

};
}

#endif