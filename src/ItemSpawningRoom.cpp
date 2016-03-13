#include "ItemSpawningRoom.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(ItemSpawningRoom);

ItemSpawningRoom::ItemSpawningRoom() : _chanceToSpawn(0.0), _maxAmount(0) {}

void ItemSpawningRoom::Update() {
	if(_items.size() < _maxAmount && Utils::RandomBool(_chanceToSpawn)){
		Item* newItem = _spawnItem->Clone();
		_items.push_back(std::unique_ptr<Item>(newItem));
	}
}

void ItemSpawningRoom::SaveImplementation(std::ostream& os) const {
	Room::SaveImplementation(os);
	os << _chanceToSpawn << ' ';
	os << _maxAmount << ' ';
	os << _spawnItem->Save() << ' ';
}

void ItemSpawningRoom::LoadImplementation(std::istream& is) {
	Room::LoadImplementation(is);
	is >> _chanceToSpawn;
	is >> _maxAmount;
	_spawnItem = IO::ParseObject<Item>(is);
}

}