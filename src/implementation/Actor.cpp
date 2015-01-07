#include "Actor.hpp"
#include "Room.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(Actor);

void Actor::InitCommandMap(){
		ENTRY(Actor, "go", 	   	  Go, 	   	 "Moves the player to the room in the given direction.");
		ENTRY(Actor, "take", 	  Take, 	 "Takes the given item.");
		ENTRY(Actor, "drop", 	  Drop, 	 "Drops the given item.");
		ENTRY(Actor, "inventory", Inventory, "Prints a list of the players inventory.");
}

Actor::Actor() {
	InitCommandMap();
}

Actor::~Actor() {}

void Actor::SetLocation(Room* room) {
	_location = room;
}

void Actor::AddItem(std::unique_ptr<Item>& item) {	
	_items.push_back(std::move(item));
}

std::vector<std::unique_ptr<Item>>& Actor::Items() {
	return _items;
}

Room* Actor::Location() const {
	return _location;
}

//------------------------------------------------------------
// Commands
//------------------------------------------------------------

Actor::Result Actor::Go(const std::vector<std::string>& command) {
	std::stringstream ss;
	bool goForward = false;

	if(command.size() == 0){
		ss << COLOR(direction, RED) << 
			"You need to specify a direction. You can walk the following directions: " << std::endl;
		Utils::PrintListInColors(ss, _location->Directions(), { Format::BLUE, Format::CYAN });
		return Result(ss.str(), false);
	}

	std::string direction = command[0];
	Room* nextRoom = _location->Neighbour(direction);
	if(nextRoom){
		std::unique_ptr<Actor> thisActor = _location->Leave(this);
		nextRoom->Enter(thisActor);
		_location = nextRoom;
		goForward = true;
		ss << "You went " << COLOR(direction, GREEN) << "." << std::endl;
	}else{
		ss << COLOR(direction, RED) << 
			" is not a valid direction. You can walk the following directions: " << std::endl;
		Utils::PrintListInColors(ss, _location->Directions(), { Format::BLUE, Format::CYAN });
	}

	return Result(ss.str(), goForward);
}

Actor::Result Actor::Take(const std::vector<std::string>& command) {
	std::stringstream ss;
	bool goForward = false;

	if(command.size() == 0){
		ss << "You need to specify what you want to take." << std::endl;
		return Result(ss.str(), false);
	}

	std::string itemName = Utils::Concatenate(command);
	std::unique_ptr<Item> item = _location->RemoveItem(itemName);
	if(item){
		AddItem(item);
		ss << "You took " << COLOR(itemName, GREEN) << "." << std::endl;
		goForward = true;
	}else{
		ss << "There is no item called " << COLOR(itemName, RED) << 
			" in this room!" << std::endl;
	}
	
	return Result(ss.str(), goForward);
}

Actor::Result Actor::Drop(const std::vector<std::string>& command){
	return Result();
}

Actor::Result Actor::TalkTo(const std::vector<std::string>& command){
	return Result();
}

Actor::Result Actor::Use(const std::vector<std::string>& command){
	return Result();
}

Actor::Result Actor::Inventory(const std::vector<std::string>& command){
	std::stringstream ss;
	if(_items.size() == 0){
		ss << "You have no items." << std::endl;
	}else{
		ss << "You have the following items:" << std::endl;
		Utils::PrintListInColors(ss, _items, { Format::BLUE, Format::CYAN });
	}
	return Result(ss.str(), false);
}

void Actor::SaveImplementation(std::ostream& os) const {
	IO::PrintList(os, _items);
}

void Actor::LoadImplementation(std::istream& is) {
	_items = IO::ParseList<Item>(is);
}

}
