#ifndef LAB3__ACTOR_SPAWNING_ROOM
#define LAB3__ACTOR_SPAWNING_ROOM

#include "Item.hpp"
#include "FightingActor.hpp"
#include "Room.hpp"


namespace Lab3{

class TeleporterRoom : public Room {
public:

	TeleporterRoom();
	TeleporterRoom(const TeleporterRoom& rhs);
	~TeleporterRoom();

	virtual Room* Clone() const override;

	virtual void Update() override;

protected:

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& is) override;

private:

	Room* ConstructNewRoom();
	std::string GetRoomName() const;
	FightingActor* ConstructActor() const;
	std::string GetActorName() const;


	size_t _timeWaited;
	std::unique_ptr<Actor> _baseActor;
	std::vector<Room*> _spawnedRooms;

	IO_FACTORY_REGISTER_DECL(TeleporterRoom);

};

}

#endif