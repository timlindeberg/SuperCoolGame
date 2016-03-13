#include "Actor.hpp"
#include "Room.hpp"

namespace Lab3{

Actor::Actor() {}

Actor::Actor(const Actor& rhs){
	_name = rhs._name;
	_description = rhs._description;
	_location = rhs._location;
	for(auto& item : _items){
		_items.push_back(std::unique_ptr<Item>(item->Clone()));
	}
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

bool Actor::Go(const std::string& direction){
	if(_location->IsLocked(direction)){
		return false;
	}
	Room* nextRoom = _location->Neighbour(direction);
	std::unique_ptr<Actor> thisActor = _location->RemoveActor(this);
	nextRoom->AddActor(thisActor);
	_location = nextRoom;
	return true;
}

bool Actor::TryUnlock(const std::string& direction){
	const std::string& requiredKey = _location->RequiredKey(direction);
	for(auto& item : _items){
		if(Utils::SameName(item, requiredKey)){
			_location->Unlock(direction);
			return true;
		}
	}
	return false;
}

void Actor::Take(const std::string& itemName) {
	std::unique_ptr<Item> item = _location->RemoveItem(itemName);
	AddItem(item);
}

void Actor::Drop(const std::string& itemName){
	std::unique_ptr<Item> item = Utils::RemoveItem(_items, itemName);
	_location->AddItem(item);
}

void Actor::TalkTo(const std::string& actorName) {

}

void Actor::SaveImplementation(std::ostream& os) const {
	os << _name << ' ';
	IO::PrintString(os, _description);
	IO::PrintList(os, _items);
}

void Actor::LoadImplementation(std::istream& is) {
	_items = IO::ParseList<Item>(is);
}

std::ostream& operator<<(std::ostream& os, const Lab3::Actor& e){
	os << e.Type() << Format::FG_DEFAULT << " - " <<
	 	 COLOR(e.Name(), BLUE) <<  COLOR(": ", FG_DEFAULT) << e._description;
	return os;
}

}
