#include "Actor.hpp"
#include "Room.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(Actor);

void Actor::InitCommandMap(){
	#define ENTRY(name, func) _commandMap[name] = std::bind(&Actor::func, this, std::placeholders::_1)
		
		ENTRY("go", Go);
		ENTRY("take", Take);
		ENTRY("drop", Drop);
		ENTRY("inventory", Inventory);
	
	#undef ENTRY
}

Actor::Actor() {
	InitCommandMap();
}

Actor::Actor(std::string name) : IO(name) {}

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

bool Actor::Go(const std::vector<std::string>& command) {
	std::string direction = command[0];
	Room* nextRoom = _location->Neighbour(direction);
	if(!nextRoom){
		std::cout << COLOR(direction, RED) << 
			" is not a valid direction. You can walk the following directions: " << std::endl;
		for(auto& s : _location->Directions()){
			std::cout << "\t" << COLOR(s, YELLOW);
		}
		return false;
	}
	std::unique_ptr<Actor> thisActor = _location->Leave(this);
	nextRoom->Enter(thisActor);
	_location = nextRoom;
	return true;
}

bool Actor::Take(const std::vector<std::string>& command) {
	std::string itemName;
	for(auto& s : command)
		itemName.append(s);
	std::unique_ptr<Item> item = _location->RemoveItem(itemName);
	if(!item){
		std::cout << "There is no item called " << COLOR(itemName, RED) << 
			" in this room!" << std::endl;
		return false;
	}
	AddItem(item);
	std::cout << "You took " << COLOR(itemName, GREEN) << "." << std::endl;
	return true;
}

bool Actor::Drop(const std::vector<std::string>& command){
	return true;
}

bool Actor::TalkTo(const std::vector<std::string>& command){
	return true;
}

bool Actor::Use(const std::vector<std::string>& command){
	return true;
}

bool Actor::Inventory(const std::vector<std::string>& command){
	if(_items.size() == 0){
		std::cout << "You have no items." << std::endl;
	}else{
		std::cout << "You have the following items:" << std::endl;
		Utils::PrintListInColors(std::cout, _items, { Format::BLUE, Format::CYAN });
	}
	return true;
}

void Actor::SaveImplementation(std::ostream& os) const {
	IO::PrintList(os, _items);
}

void Actor::LoadImplementation(std::istream& is) {
	_items = IO::ParseList<Item>(is);
}

}
