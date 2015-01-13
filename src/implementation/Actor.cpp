#include "Actor.hpp"
#include "Room.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(Actor);

Actor::Actor() {}

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

bool Actor::Go(const std::vector<std::string>& command) {
	if(command.size() == 0){
		Lab3::out << BeginBox(GameStream::FAIL_COLOR);
		Lab3::out << "You need to specify a direction. You can walk the following directions" << std::endl;
		Lab3::out << Delimiter();
		Utils::PrintListInColors(Lab3::out, _location->Directions(), { Format::BLUE, Format::CYAN });
		Lab3::out << EndBox();
		return false;
	}

	std::string direction = Utils::Concatenate(command);

	Room* nextRoom = _location->Neighbour(direction);
	if(!nextRoom){
		Lab3::out << BeginBox(GameStream::FAIL_COLOR);
		Lab3::out << COLOR(direction, RED) << 
			" is not a valid direction. You can walk the following directions" << std::endl;
		Lab3::out << Delimiter();
		Utils::PrintListInColors(Lab3::out, _location->Directions(), { Format::BLUE, Format::CYAN });
		Lab3::out << EndBox();
		return false;
	}

	if(_location->IsLocked(direction)){
		bool hasKey = false;
		for(auto& item : _items){
			if(Utils::SameName(item, _location->RequiredKey(direction))){
				hasKey = true;
				_location->Unlock(direction);
				PRINT_BOX(GameStream::SUCCESS_COLOR,
					"You unlocked the door using " << COLOR(item->Name(), BLUE) << "." << std::endl);
				break;
			}
		}

		if(!hasKey){
			PRINT_BOX(GameStream::FAIL_COLOR, 
				"You can't walk " << COLOR(direction, RED) << ", the door is locked!" << std::endl);
			return false;
		}
		
	}

	std::unique_ptr<Actor> thisActor = _location->RemoveActor(this);
	nextRoom->AddActor(thisActor);
	_location = nextRoom;
	PRINT_BOX(GameStream::SUCCESS_COLOR,
		"You went " << COLOR(direction, GREEN) << "." << std::endl);
	return true;
}

bool Actor::Take(const std::vector<std::string>& command) {
	if(command.size() == 0){
		PRINT_BOX(GameStream::FAIL_COLOR,
			"You need to specify what you want to take." << std::endl);
		return false;
	}

	std::string itemName = Utils::Concatenate(command);
	std::unique_ptr<Item> item = _location->RemoveItem(itemName);
	if(!item){
		PRINT_BOX(GameStream::FAIL_COLOR,
			"There is no item called " << COLOR(itemName, RED) << 
			" in this room!" << std::endl);
		return false;
	}
	std::string name = item->Name();
	AddItem(item);
	PRINT_BOX(GameStream::SUCCESS_COLOR,
		"You took " << COLOR(name, GREEN) << "." << std::endl);
	return true;
}

bool Actor::Drop(const std::vector<std::string>& command){
	if(command.size() == 0){
		PRINT_BOX(GameStream::FAIL_COLOR,
			"You need to specify what you want to drop." << std::endl);
		return false;
	}

	std::string itemName = Utils::Concatenate(command);
	std::unique_ptr<Item> item = Utils::RemoveItem(_items, itemName);

	if(!item){
		PRINT_BOX(GameStream::FAIL_COLOR,
			"You have no item called " << COLOR(itemName, RED) << std::endl);
		return false;
	}

	std::string name = item->Name();
	_location->AddItem(item);
	PRINT_BOX(GameStream::SUCCESS_COLOR,
		"You dropped " << COLOR(name, GREEN) << "." << std::endl);
	return true;
}

bool Actor::TalkTo(const std::vector<std::string>& command) {
	if(command.size() == 0) {
		PRINT_BOX(GameStream::FAIL_COLOR,
			"You need to specify what you want to drop." << std::endl);
		return false;
	}

	return false;
}

void Actor::SaveImplementation(std::ostream& os) const {
	os << _name << ' ';
	IO::PrintDescription(os, _description);
	IO::PrintList(os, _items);
}

void Actor::LoadImplementation(std::istream& is) {
	_items = IO::ParseList<Item>(is);
}

std::ostream& operator<<(std::ostream& os, const Lab3::Actor& e){
	os << e.Name() <<  COLOR(": ", FG_DEFAULT) << e._description;
	return os;
}



}
