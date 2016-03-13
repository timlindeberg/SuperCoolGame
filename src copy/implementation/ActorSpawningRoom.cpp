#include "ActorSpawningRoom.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(ActorSpawningRoom);

ActorSpawningRoom::ActorSpawningRoom() : _id(1), _chanceToSpawn(0.0), _maxAmount(0) {}

void ActorSpawningRoom::Update() {
	if(_actors.size() < _maxAmount && Utils::RandomBool(_chanceToSpawn)){
		Actor* actor = _spawnItem->Clone();
		std::stringstream ss;
		ss << _spawnItem->Name() << _id++;
		std::string newName = ss.str();
		actor->SetName(ss.str());
		_actors.push_back(std::unique_ptr<Actor>(actor));
	}
}

void ActorSpawningRoom::SaveImplementation(std::ostream& os) const {
	Room::SaveImplementation(os);
	os << _id << ' ';
	os << _chanceToSpawn << ' ';
	os << _maxAmount << ' ';
	os << _spawnItem->Save() << ' ';
}

void ActorSpawningRoom::LoadImplementation(std::istream& is) {
	Room::LoadImplementation(is);
	is >> _id;
	is >> _chanceToSpawn;
	is >> _maxAmount;
	_spawnItem = IO::ParseObject<Actor>(is);
	_spawnItem->SetLocation(this);
}

}