#ifndef LAB3__ACTOR_SPAWNING_ROOM
#define LAB3__ACTOR_SPAWNING_ROOM

#include "Item.hpp"
#include "Room.hpp"


namespace Lab3{

class ActorSpawningRoom : public Room {
public:

	ActorSpawningRoom();

	virtual void Update() override;

protected:

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& is) override;

private:

	size_t _id;
	double _chanceToSpawn;
	size_t _maxAmount;
	std::unique_ptr<Actor> _spawnItem;

	IO_FACTORY_REGISTER_DECL(ActorSpawningRoom);

};

}

#endif