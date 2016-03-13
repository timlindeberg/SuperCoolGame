#ifndef LAB3__ENVIRONMENT
#define LAB3__ENVIRONMENT

#include <vector>
#include <map>
#include <iostream>
#include <exception>
#include <cctype>

#include "IO.hpp"
#include "Item.hpp"
#include "Utils.hpp"
#include "Format.hpp"
#include "Player.hpp"


namespace Lab3{

class Actor;
class Game;
class Room : public IO {

public:

	// Constructors

	Room();
	Room(const std::string& name);
	Room(const Room& rhs); 
	
	virtual Room* Clone() const;

	virtual ~Room();

	// Methods

	void PrintDescription() const;

	std::vector<std::string> Directions() const;
	Room* Neighbour(const std::string& direction) const;

	bool IsLocked(const std::string& direction) const;
	const std::string& RequiredKey(const std::string& direction) const;
	void Unlock(const std::string& direction);

	std::vector<std::unique_ptr<Item>>& Items();
	void AddItem(std::unique_ptr<Item>& item);
	std::unique_ptr<Item> RemoveItem(const std::string& item);

	std::vector<std::unique_ptr<Actor>>& Actors();
	void AddActor(std::unique_ptr<Actor>& actor);
	std::unique_ptr<Actor> RemoveActor(Actor* actor);

	// Events
	virtual void OnEnter(Actor* actor);
	virtual void OnLeave(Actor* actor);
	virtual void Update();

	void AddExit(const std::string& dir, Room* e);
	void SetUpExits(const std::vector<std::unique_ptr<Room>>& environments);


protected:

	struct CompareDirection {
		bool operator()(const std::string& a, const std::string& b) const;
	};

	typedef std::map<std::string, Room*, CompareDirection> ExitMap;
	typedef std::map<std::string, std::string, CompareDirection> LockedMap;

	ExitMap _exits;
	LockedMap _locked;
	std::vector<std::unique_ptr<Actor>> _actors;
	std::vector<std::unique_ptr<Item>> _items;

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& is) override;

private:

	IO_FACTORY_REGISTER_DECL(Room);
};

}

#endif