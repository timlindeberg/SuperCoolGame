#include "TeleporterRoom.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(TeleporterRoom);

TeleporterRoom::TeleporterRoom() {}

TeleporterRoom::TeleporterRoom(const TeleporterRoom& rhs) : Room(rhs) {
	for(auto& room : rhs._spawnedRooms){
		_spawnedRooms.push_back(room->Clone());
	}
}

TeleporterRoom::~TeleporterRoom() {
	for(auto& room : _spawnedRooms){
		delete room;
	}
}

void TeleporterRoom::Update() {
	static const size_t waitTime = 4;
	static const size_t maxRooms = 25;

	if(_spawnedRooms.size() >= maxRooms)
		return;

	if(_timeWaited++ <= waitTime)
		return;

	_timeWaited = 0;
	Room* room = ConstructNewRoom();
	_spawnedRooms.push_back(room);
	AddExit(room->Name(), room);
}

Room* TeleporterRoom::ConstructNewRoom() {
	std::string name = GetRoomName();
	Room* room = new Room(name);
	room->AddExit("Teleport", this);
	for(size_t i = 0; i < Utils::RandomInt(0, 5); ++i){
		std::unique_ptr<Actor> alien(ConstructActor());
		alien->SetLocation(room);
		room->AddActor(alien);
	}
	return room;
}

std::string TeleporterRoom::GetRoomName() const {
	static const size_t numLetters = 3;
	static const size_t numNumbers = 2;

	std::stringstream ss;
	for(size_t i = 0; i < numLetters; ++i)
		ss << Utils::RandomLetter();
	for(size_t i = 0; i < numNumbers; ++i)
		ss << Utils::RandomInt(0, 9);
	return ss.str();

}

FightingActor* TeleporterRoom::ConstructActor() const {
	#define STAT(stat) Utils::NormalDistFloat(1, 0.3) * stats.stat()

	FightingActor* actor = dynamic_cast<FightingActor*>(_baseActor->Clone());
	Stats stats = actor->GetStats();
	Stats newStats(STAT(HP), STAT(AP), STAT(Agility), STAT(Intelligence));
	actor->SetStats(newStats);
	actor->SetHP(newStats.HP());
	actor->SetName(GetActorName());

	return actor;
	#undef SET_STAT
}

std::string TeleporterRoom::GetActorName() const {
	static size_t ID = 1;
	std::stringstream ss;
	ss << _baseActor->Name() << ID++;
	return ss.str();
}

Room* TeleporterRoom::Clone() const {
	return new TeleporterRoom(*this); 
}

void TeleporterRoom::SaveImplementation(std::ostream& os) const {
	Room::SaveImplementation(os);
	os << _timeWaited << ' ';
	os << _baseActor->Save() << ' ';
	IO::PrintList(os, _spawnedRooms);
}

void TeleporterRoom::LoadImplementation(std::istream& is){
	Room::LoadImplementation(is);
	is >> _timeWaited;
	_baseActor = IO::ParseObject<FightingActor>(is);
	_baseActor->SetLocation(this);
	_spawnedRooms = IO::ParseListRaw<Room>(is);

	for(auto& room : _spawnedRooms){
		room->AddExit("Teleport", this);
		AddExit(room->Name(), room);
		for(auto& actor : room->Actors()){
			Player* player = dynamic_cast<Player*>(actor.get());
			if(player){
				Game::Instance()->SetPlayer(player);
			}
			actor->SetLocation(room);
		}
	}
}

}