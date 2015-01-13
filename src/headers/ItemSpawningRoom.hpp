#ifndef LAB3__ITEM_SPAWNING_ROOM
#define LAB3__ITEM_SPAWNING_ROOM

#include "Item.hpp"
#include "Room.hpp"


namespace Lab3{

class ItemSpawningRoom : public Room {
public:

	ItemSpawningRoom();
	virtual void Update() override;

protected:

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& is) override;

private:

	double _chanceToSpawn;
	size_t _maxAmount;
	std::unique_ptr<Item> _spawnItem;

	IO_FACTORY_REGISTER_DECL(ItemSpawningRoom);

};

}

#endif