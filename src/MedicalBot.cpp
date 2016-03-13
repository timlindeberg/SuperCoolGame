#include "MedicalBot.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(MedicalBot);

MedicalBot::MedicalBot() : 
	_healAmount(0),
	_timeWaited(0),
	_healsUsed(0)
{}

Actor* MedicalBot::Clone() const{
	return new MedicalBot(*this); 
}

bool MedicalBot::JoinBattle() const {
	return true;
}

void MedicalBot::Action(){
	static const size_t waitTime = 3;
	static const double healThreshold = 0.7;

	if(_timeWaited++ <= waitTime){
		return;
	}
	_timeWaited = 0;
	for(auto& actor : _location->Actors()){
		FightingActor* fightingActor = dynamic_cast<FightingActor*>(actor.get());
		if(fightingActor){
			if(fightingActor->HPPercentage() <= healThreshold){
				HealActor(fightingActor);
				break;
			}
		}
	}
}	

void MedicalBot::HealActor(FightingActor* fightingActor){
	Player* player = Game::Instance()->GetPlayer();
	int HPbefore = fightingActor->HP();
	fightingActor->TakeHeal(_healAmount);
	if(player->Location() == _location){
		int HPhealed = fightingActor->HP() - HPbefore;
		PRINT_BOX(GameStream::SUCCESS_COLOR,
			COLOR(_name, CYAN) << " healed " <<
			COLOR(fightingActor->Name(), BLUE) << " for " <<
			COLOR(HPhealed, GREEN) << " HP." << std::endl);
	}
}

void MedicalBot::BattleAction(const std::vector<FightingActor*>& otherActors){
	static const size_t maxHeals = 3;
	static const double healThreshold = 0.7;
	if(_healsUsed >= maxHeals){
		PRINT_BOX(GameStream::SUCCESS_COLOR,
			COLOR(_name, CYAN) << " has ran out of healing energy and does nothing. " << std::endl);
		return;
	}

	for(auto& actor : _location->Actors()){
		FightingActor* fightingActor = dynamic_cast<FightingActor*>(actor.get());
		if(fightingActor){
			if(fightingActor->HPPercentage() <= healThreshold){
				HealActor(fightingActor);
				++_healsUsed;
				break;
			}
		}
	}
}

void MedicalBot::SaveImplementation(std::ostream& os) const {
	FightingActor::SaveImplementation(os);
	os << _healAmount << ' ';
	os << _timeWaited << ' ';
	os << _healsUsed << ' ';
}

void MedicalBot::LoadImplementation(std::istream& is) {
	FightingActor::LoadImplementation(is);
	is >> _healAmount;
	is >> _timeWaited;
	is >> _healsUsed;
}


}