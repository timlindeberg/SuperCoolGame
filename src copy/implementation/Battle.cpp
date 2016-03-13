#include "Battle.hpp"
#include "FightingActor.hpp"

namespace Lab3{

Battle* Battle::_instance = nullptr;


Battle::Battle(FightingActor* actor) {
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
	if(actor)
		_actors.push_back(actor);
	else
		pr("added null actor");
}

void Battle::RemoveActor(FightingActor* actor){
	*(std::find(_actors.begin(), _actors.end(), actor)) = nullptr;
}

std::vector<FightingActor*>& Battle::Actors() {
	return _actors;
}

void Battle::Start(){
	_isRunning = true;

	auto SortByAgility = [](FightingActor* a1, FightingActor* a2) -> bool {
		return a1->GetStats().Agility() > a2->GetStats().Agility();
	};

	std::sort(_actors.begin(), _actors.end(), SortByAgility);

	while(_actors.size() > 1 && _isRunning && Game::Instance()->IsRunning()){
		for(FightingActor* actor : _actors){
			if(actor->IsAlive())
				actor->BattleAction(_actors);
			if(!_isRunning)
				break;
		}
		for(auto it = _actors.begin(); it != _actors.end();){
			FightingActor* actor = *it;
			if(!actor->IsAlive()){
				actor->Kill();
				it = _actors.erase(it);
				if(_actors.size() <= 1){
					PRINT_BOX(GameStream::BATTLE_COLOR,
						"You " << COLOR("won", GREEN) << " the battle!" << std::endl);
				}
			}else if(actor->Fled()){
				it = _actors.erase(it);
			}else{
				++it;
			}
		}
	}
}

void Battle::End() {
	_isRunning = false;
}

bool Battle::IsRunning() const {
	return _isRunning;
}

void Battle::PrintString() const{
	Lab3::out << BeginBox(GameStream::BATTLE_COLOR);
	Lab3::out << Alignment::CENTER << "Battle status" << std::endl;
	Lab3::out << Delimiter();

	int N = _actors.size();
	for(size_t i = 0; i < N; ++i){
		if(!_actors[i]) continue;
		_actors[i]->PrintBattleDescription();
		if(i != N - 1 ) Lab3::out << Delimiter();
	}

	Lab3::out << EndBox();
}

}