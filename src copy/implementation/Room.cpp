#include "Room.hpp"
#include "Actor.hpp"
#include "Game.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(Room);

Room::Room() {}
Room::Room(const std::string& name) : IO(name) {}

Room::~Room() {}

void Room::OnEnter(Actor* actor) {}

void Room::OnLeave(Actor* actor) {}

void Room::Update() {}

std::vector<std::unique_ptr<Actor>>& Room::Actors() {
	return _actors;
}

std::vector<std::unique_ptr<Item>>& Room::Items() {
	return _items;
}

std::vector<std::string> Room::Directions() const {
	std::vector<std::string> directions;
	for(auto iter : _exits)
		directions.push_back(iter.first);
	return directions;
}

Room* Room::Neighbour(std::string direction) const {
	Utils::FirstUpperCase(direction);
	try{
		return _exits.at(direction);
	}catch(std::out_of_range& e){
		return nullptr;
	}
}

bool Room::IsLocked(std::string direction) const {
	Utils::FirstUpperCase(direction);	
	return _locked.count(direction);
}

const std::string& Room::RequiredKey(std::string direction) const {
	Utils::FirstUpperCase(direction);		
	return _locked.at(direction);
}

void Room::Unlock(std::string direction){
	Utils::FirstUpperCase(direction);		
	_locked.erase(_locked.find(direction));
}

void Room::AddItem(std::unique_ptr<Item>& item){
	Utils::AddItem(_items, item);
}

std::unique_ptr<Item> Room::RemoveItem(const std::string& item) {
	return Utils::RemoveItem(_items, item);	
}

void Room::AddExit(const std::string& dir, Room* e) {
	_exits[dir] = e;
}

std::unique_ptr<Actor> Room::RemoveActor(Actor* actor) {
	return Utils::RemoveItem(_actors, actor->Name());
}

void Room::AddActor(std::unique_ptr<Actor>& actor) {
	Utils::AddItem(_actors, actor);
}

// IO

void Room::SaveImplementation(std::ostream& os) const {
	os << _name << ' ';
	IO::PrintString(os, _description);
	IO::PrintList(os, _actors);
	IO::PrintList(os, _items);
	
	os << IO::LIST_START << ' ';
	size_t i = 0;
	for(auto& iter : _exits){
		os << iter.first << IO::MAP_SEP << iter.second->Name();
		if(IsLocked(iter.first)){
			os << IO::MAP_SEP << RequiredKey(iter.first);
		}
		os << ' ';
		if(i < _exits.size() - 1){
			os << IO::LIST_SEP << ' ';
		}
		i++;
	}
	os << IO::LIST_END << ' ';
}

void Room::LoadImplementation(std::istream& is) {
	_actors = IO::ParseList<Actor>(is);
	for(auto& a : _actors){
		a->SetLocation(this);
	}
	_items = IO::ParseList<Item>(is);

	// Create temporary placeholders so we can link the rooms together later
	std::string exitList = IO::ReadList(is);
	for(const std::string& s : Utils::Split(exitList, ' ')){
		if(s[0] == IO::LIST_SEP){
			continue;
		}

		std::vector<std::string> exit = Utils::Split(s, IO::MAP_SEP);
		_exits[exit[0]] = new Room(exit[1]);
		if(exit.size() == 3){
			_exits[exit[0]]->_locked[exit[0]] = exit[2];
		}
	}
}

void Room::SetUpExits(const std::vector<std::unique_ptr<Room>>& rooms) {
	for(auto& iter : _exits){
		for(auto& room : rooms){
			Room*& tmpRoom = iter.second;
			if(Utils::SameName(tmpRoom, room)){
				const std::string& direction = iter.first;
				if(tmpRoom->IsLocked(direction)){
					_locked[direction] = tmpRoom->_locked[direction];
				}
				delete tmpRoom;
				tmpRoom = room.get();
				break;
			}
		}
	}
}

void Room::PrintString() const{
	static const std::initializer_list<Format::Code> listColors = {Format::BLUE, Format::CYAN };
	Lab3::out << BeginBox(GameStream::ROOM_COLOR);

	Lab3::out << _description << std::endl;
	if(_actors.size() > 1){
		Lab3::out << Delimiter();
		Lab3::out << Alignment::CENTER << STYLE("Characters in this room", BOLD) << std::endl;
		std::vector<Actor*> actors;
		for(auto& a : _actors){
			Actor* actor = a.get();
			if(dynamic_cast<Player*>(actor)) {   // Ignore player when printing
				continue;
			}
			actors.push_back(actor);
		}
		Utils::PrintListInColors(Lab3::out, actors, listColors);
	}

	if(_items.size() >= 1){
		Lab3::out << Delimiter();
		Lab3::out << Alignment::CENTER << STYLE("Items in this room", BOLD) << std::endl;
		Utils::PrintListInColors(Lab3::out, _items, listColors);
	}

	if(_exits.size() >= 1){
		Lab3::out << Delimiter();
		Lab3::out << Alignment::CENTER << STYLE("Exits", BOLD) << std::endl;
		Utils::PrintListInColors(Lab3::out, Directions(), listColors);
	}

	Lab3::out << EndBox();
}

}