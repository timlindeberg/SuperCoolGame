#ifndef __LAB3__GAME__
#define __LAB3__GAME__

#include <fstream>
#include "IO.hpp"
#include "Entity.hpp"
#include "Environment.hpp"
#include "Actor.hpp"

namespace Lab3{

class Game : public IO {
	
public:

	// Methods
	static Game* Instance();
	
	Game();
	void Run();
	Entity* GetPlayer() const;
	bool IsRunning() const;
	bool SaveGame(const std::string& fileName) const;
	bool LoadGame(const std::string& fileName);

protected:

	void SaveImplementation(std::ostream& os) const;
	void LoadImplementation(std::istream& is);

private:

	static Game* _instance;
	bool _isRunning;
	std::vector<Environment> _environments;
	std::vector<Entity> _entities;
	std::vector<Actor> _actors;

	Entity* _player;

};
}

#endif