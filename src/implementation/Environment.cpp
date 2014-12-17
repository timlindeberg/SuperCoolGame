#include "Environment.hpp"
using namespace Lab3;

Environment::Environment() {};
Environment::Environment(std::string name) : _name(name), _entities(), _exits() {};

std::vector<std::string> Environment::Directions() const
{

}

std::string Environment::Name() const{
	return _name;
}

void Environment::Drop(Entity& entity){
	_entities.push_back(&entity);
}

void Environment::AddExit(std::string dir, Environment& e){
	_exits[dir] = &e;
} 

// IO

void Environment::SaveImplementation(std::ostream& os) const{
	os << IO::OBJECT_SEP;
	os << _name;
	os << IO::LIST_SEP << ' ';
	for(Entity* e : _entities){
		os << e->Name() << ' ';
	}
	os << IO::LIST_SEP << ' ';
	os << IO::LIST_SEP << ' ';
	for(auto iter : _exits){
		os << iter.first << IO::MAP_SEP << iter.second->Name() << ' ';
	}
	os << IO::LIST_SEP << ' ';
	os << IO::OBJECT_SEP;
}

void Environment::LoadImplementation(std::istream& is){
	std::stringstream ss;
	ss << IO::ReadObject(is);
	ss >> _name;
	// Create temporary placeholders so we can link the rooms togheter later

	// First list is the entities
	for(const std::string& s : IO::ReadList(ss)){
		_entities.push_back(new Entity(s, -1, -1));
	}

	// Second list is the exits
	for(const std::string& s : IO::ReadList(ss)){
		std::vector<std::string> exit = Utils::Split(s, IO::MAP_SEP);
		_exits[exit[0]] = new Environment(exit[1]);
	}
}


