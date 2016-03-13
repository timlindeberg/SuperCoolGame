#include "Hunter.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(Hunter);

Hunter::Hunter() : _roundsWaited(0), _playerInSameRoom(false)  {}

Actor* Hunter::Clone() const {
	return new Hunter(*this); 
}

bool Hunter::JoinBattle() const {
	return true;
}

void Hunter::Action(){
	static const size_t waitTime = 3;

	if(Battle::Instance()) return;
	Player* player = Game::Instance()->GetPlayer();
	if(_playerInSameRoom){
		PRINT_BOX(GameStream::SUCCESS_COLOR,
			_name << " attacks you!" << std::endl);
		Fight(player);
	}
	_playerInSameRoom = player->Location() == _location;
	if(_playerInSameRoom){
		return;
	}
	if(_roundsWaited++ < waitTime){
		return; 
	}
	_roundsWaited = 0;
	Room* room = FindNextRoom();
	if(!room)
		return;

	for(auto& direction : _location->Directions()){
		if(_location->Neighbour(direction) == room){
			Go(direction);
			return;
		}
	}	
}

void Hunter::BattleAction(const std::vector<FightingActor*>& otherActors){
	Attack(Game::Instance()->GetPlayer());
}

Room* Hunter::FindNextRoom() const {
	std::map<Room*, Room*> parentMap;

	if(DFS(parentMap)){
		return FindNextRoom(parentMap);
	}
	
	return nullptr;
}

bool Hunter::DFS(std::map<Room*, Room*>& parentMap) const{
	Room* playerRoom = Game::Instance()->GetPlayer()->Location();
	std::vector<Room*> stack;
	stack.push_back(_location);
	std::map<Room*, bool> visited;

	bool playerFound = false;
	while(!stack.empty()){
		Room* room = stack.back();
		stack.pop_back();
		if(visited[room]){
		 	continue;
		}
		visited[room] = true;
		if(room == playerRoom){
			playerFound = true;
			return true;
		}
		for(auto& direction : room->Directions()){
			if(!room->IsLocked(direction)){
				Room* neighbour = room->Neighbour(direction);
				if(visited[neighbour]){
					continue;
				}
				stack.push_back(neighbour);
				parentMap[neighbour] = room;
			}
		}
	}
	return false;
}

Room* Hunter::FindNextRoom(std::map<Room*, Room*>& parentMap) const{
	Room* playerRoom = Game::Instance()->GetPlayer()->Location();

	Room* currentRoom;
	Room* nextRoom = playerRoom; 
	do{
		currentRoom = nextRoom;
		nextRoom = parentMap[currentRoom];
	}while(nextRoom != _location);
	return currentRoom;
}

void Hunter::SaveImplementation(std::ostream& os) const {
	FightingActor::SaveImplementation(os);
	os << _roundsWaited << ' ';
}

void Hunter::LoadImplementation(std::istream& is){
	FightingActor::LoadImplementation(is);
	is >> _roundsWaited;
}

}