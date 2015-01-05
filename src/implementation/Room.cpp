#include "Room.hpp"
#include "Actor.hpp"


namespace Lab3{

IO_FACTORY_REGISTER_DEF(Room);

Room::Room() {}

Room::Room(std::string name) : IO(name), _exits(), _actors(), _items() {}

Room::~Room() {}

void Room::OnEnter(Actor* actor) {}

void Room::OnLeave(Actor* actor) {}

void Room::Update() {}

std::vector<std::unique_ptr<Actor>>& Room::GetActors() {
	return _actors;
}

const std::string& Room::Description() const {
	return _description;
}

std::vector<std::string> Room::Directions() const {
	std::vector<std::string> directions;
	for(auto iter : _exits)
		directions.push_back(iter.first);
	return directions;
}

Room* Room::Neighbour(const std::string& direction) const {
	std::string d = direction;
	d[0] = std::toupper(d[0]);
	try{
		return _exits.at(d);
	}catch(std::out_of_range& e){
		return nullptr;
	}
}

void Room::AddItem(std::unique_ptr<Item>& item){
	_items.push_back(std::move(item));
}

std::unique_ptr<Item> Room::RemoveItem(const std::string& item) {
	for(auto it = _items.begin(); it != _items.end(); ++it){
		if((*it)->Name() == item){
			std::unique_ptr<Item> ptr = std::move(*it);
			_items.erase(it);
			return ptr;
		} 
	}
	return std::unique_ptr<Item>(nullptr);
}

void Room::AddExit(const std::string& dir, Room* e) {
	_exits[dir] = e;
}

std::unique_ptr<Actor> Room::Leave(Actor* actor) {
	for(auto it = _actors.begin(); it != _actors.end(); ++it){
		if(it->get() == actor){
			std::unique_ptr<Actor> ptr = std::move(*it);
			_actors.erase(it);
			OnLeave(actor);
			return ptr;
		} 
	}
	return std::unique_ptr<Actor>(nullptr);
}

void Room::Enter(std::unique_ptr<Actor>& actor) {
	_actors.push_back(std::move(actor));
	OnEnter(actor.get());
}


// IO

void Room::SaveImplementation(std::ostream& os) const {
	os << IO::DESC_SIGN << ' ';
	os << _description << ' ';
	os << IO::DESC_SIGN << ' ';

	IO::PrintList(os, _actors);
	IO::PrintList(os, _items);
	
	os << IO::LIST_START << ' ';
	size_t i = 0;
	for(auto& iter : _exits){
		os << iter.first << IO::MAP_SEP << iter.second->Name() << ' ';
		if(i < _exits.size() - 1){
			os << IO::LIST_SEP << ' ';
		}
		i++;
	}
	os << IO::LIST_END << ' ';
}

void Room::LoadImplementation(std::istream& is) {
	_description = IO::ReadDescription(is);
	_actors = IO::ParseList<Actor>(is);
	for(auto& a : _actors){
		a->SetLocation(this);
	}
	_items = IO::ParseList<Item>(is);
	// Create temporary placeholders so we can link the rooms together later
	// Second list is the exits
	std::string exitList = IO::ReadList(is);
	for(const std::string& s : Utils::Split(exitList, ' ')){
		if(s[0] == IO::LIST_SEP){
			continue;
		}

		std::vector<std::string> exit = Utils::Split(s, IO::MAP_SEP);
		_exits[exit[0]] = new Room(exit[1]);
	}
}

void Room::SetUpExits(const std::vector<std::unique_ptr<Room>>& environments) {
	for(auto& iter : _exits){
		for(auto& e : environments){
			if(iter.second->Name() == e->Name()){
				delete iter.second;
				iter.second = e.get();
			}
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Lab3::Room& env) {
	static std::initializer_list<Format::Code> listColors = {Format::BLUE, Format::CYAN };

	os << env._description << std::endl;
	if(env._actors.size() > 1){
		os << std::endl;
		os << STYLE("Characters in this room:", BOLD) << std::endl;
		std::vector<Actor*> actors;
		for(auto& a : env._actors){
			Actor* actor = a.get();
			if(dynamic_cast<Player*>(actor)) {   // Ignore player when printing
				continue;
			}
			actors.push_back(actor);
		}
		Utils::PrintListInColors(os, actors, listColors);
	}

	if(env._items.size() >= 1){
		os << std::endl;
		os << STYLE("Items in this room:", BOLD) << std::endl;
		Utils::PrintListInColors(os, env._items, listColors);
	}

	if(env._exits.size() >= 1){
		os << std::endl;
		os << STYLE("Exits:", BOLD) << std::endl;
		Utils::PrintListInColors(os, env.Directions(), listColors);
	}
	return os;
}

}