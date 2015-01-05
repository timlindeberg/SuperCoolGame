#ifndef LAB3__ENVIRONMENT
#define LAB3__ENVIRONMENT

#include <vector>
#include <map>
#include <iostream>
#include <exception>

#include "IO.hpp"
#include "Item.hpp"
#include "Utils.hpp"
#include "Format.hpp"
#include "Player.hpp"


namespace Lab3{

class Actor;
class Room : public IO {

public:
	
	// Constructors

	Room();
	Room(std::string name);
	virtual ~Room();

	// Methods

	const std::string& Description() const;
	void PrintDirections() const;
	std::vector<std::string> Directions() const;
	Room* Neighbour(const std::string& direction) const;

	void AddItem(std::unique_ptr<Item>& item);
	std::unique_ptr<Item> RemoveItem(const std::string& item);

	std::unique_ptr<Actor> Leave(Actor* actor);
	void Enter(std::unique_ptr<Actor>& actor);

	// Events
	virtual void OnEnter(Actor* actor);
	virtual void OnLeave(Actor* actor);
	virtual void Update();


	std::vector<std::unique_ptr<Actor>>& GetActors();
	void AddExit(const std::string& dir, Room* e);
	void SetUpExits(const std::vector<std::unique_ptr<Room>>& environments);
	friend std::ostream& operator<<(std::ostream& os, const Room& env);

protected:

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& is) override;

	std::string _description;

private:

	std::map<std::string, Room*> _exits;
	std::vector<std::unique_ptr<Actor>> _actors;
	std::vector<std::unique_ptr<Item>> _items;

	IO_FACTORY_REGISTER_DECL(Room);
};

}

#endif