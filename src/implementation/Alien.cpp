#include "Alien.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(Alien);

void Alien::BattleAction(const std::vector<FightingActor*>& otherActors){
	if(Utils::RandomBool(0.2)){
		std::string& direction = Utils::RandomElement(_location->Directions());
		Run(_location->Neighbour(direction));
	}else{
		Attack(Game::Instance()->GetPlayer());
	}
}

}