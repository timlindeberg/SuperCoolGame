#include "Environment.hpp"
namespace Lab3{

IO_FACTORY_REGISTER_DEF(Environment);

Environment::Environment() {}
Environment::Environment(std::string name) : IO(name), _entities(), _exits() {}

const std::string& Environment::Description() const {
	return _description;
}

std::vector<std::string> Environment::Directions() const {

}

void Environment::Drop(Entity& entity){

}

void Environment::AddExit(const std::string& dir, Environment* e){
	_exits[dir] = e;
} 

// IO

void Environment::SaveImplementation(std::ostream& os) const{
	os << IO::DESC_SIGN << ' ';
	os << _description << ' ';
	os << IO::DESC_SIGN << ' ';

	IO::PrintList(os, _actors);
	IO::PrintList(os, _entities);
	
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

void Environment::LoadImplementation(std::istream& is){
	_description = IO::ReadDescription(is);
	_actors = IO::ParseList<Actor>(is);
	_entities = IO::ParseList<Entity>(is);
	// Create temporary placeholders so we can link the rooms together later
	// Second list is the exits
	std::string exitList = IO::ReadList(is);
	for(const std::string& s : Utils::Split(exitList, ' ')){
		if(s[0] == IO::LIST_SEP){
			continue;
		}

		std::vector<std::string> exit = Utils::Split(s, IO::MAP_SEP);
		_exits[exit[0]] = new Environment(exit[1]);
	}
}

void Environment::SetUpExits(const std::vector<std::unique_ptr<Environment>>& environments){
	for(auto& iter : _exits){
		for(auto& e : environments){
			if(iter.second->Name() == e->Name()){
				delete iter.second;
				iter.second = e.get();
			}
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Lab3::Environment& env) {
	os << env._description << std::endl;
	if(env._actors.size() >= 1){
		os << std::endl;
		os << "Characters in this room:" << std::endl;
		for(auto& a : env._actors){
			os << "\t" << *a << std::endl;
		} 
	}

	if(env._entities.size() >= 1){
		os << std::endl;
		os << "Items in this room:" << std::endl;
		for(auto& e : env._entities){
			os << "\t" << *e << std::endl;
		} 
	}

	if(env._exits.size() >= 1){
		os << std::endl;
		os << "Exits:" << std::endl;
		for(auto iter : env._exits){
			os << "\t" << iter.first << std::endl;
		} 
	}
	return os;
}

}