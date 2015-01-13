#include "Battle.hpp"
#include "FightingActor.hpp"

namespace Lab3{

Battle* Battle::_instance = nullptr;


Battle::Battle(FightingActor* actor){
	SetInstance(this);
	AddActor(actor);
}

Battle::Battle(const std::initializer_list<FightingActor*>& actors){
	SetInstance(this);
	for(auto actor : actors){
		AddActor(actor);
	}
}

Battle::~Battle() {
	_instance = nullptr;
}

Battle* Battle::Instance(){
	return _instance;
}

void Battle::SetInstance(Battle* instance){
	if(_instance){
		throw std::invalid_argument("There can only be one instance of a battle at a time!");
	}
	_instance = instance;
}

void Battle::AddActor(FightingActor* actor){
	_actors.push_back(actor);
}

void Battle::RemoveActor(FightingActor* actor){
	_actors.erase(std::find(_actors.begin(), _actors.end(), actor));
}

std::vector<FightingActor*>& Battle::Actors() {
	return _actors;
}

void Battle::Start(){
	auto SortByAgility = [](FightingActor* a1, FightingActor* a2) -> bool {
		return a1->GetStats().Agility() > a2->GetStats().Agility();
	};

	std::sort(_actors.begin(), _actors.end(), SortByAgility);

	auto actorIterator = _actors.begin();

	while(_actors.size() > 1 && Game::Instance()->IsRunning()){

		if(actorIterator == _actors.end()){
		 	actorIterator = _actors.begin();
		}
		(*actorIterator)->BattleAction(_actors);
		++actorIterator;
	}
}

void Battle::PrintDescription() const{
	Lab3::out << BeginBox(GameStream::BATTLE_COLOR);
	Lab3::out << Alignment::CENTER << "Battle status" << std::endl;
	Lab3::out << Delimiter();
	for(auto& actor : _actors){
		actor->PrintBattleDescription();
		Lab3::out << Delimiter();
	}
	Lab3::out << EndBox();
}

}