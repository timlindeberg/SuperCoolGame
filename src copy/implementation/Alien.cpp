#include "Alien.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(Alien);

Alien::Alien() : _playerInSameRoom(false) {}

Actor* Alien::Clone() const{
	return new Alien(*this); 
}

bool Alien::JoinBattle() const {
	return Utils::RandomBool(0.8);
}

void Alien::Action(){
	static double chanceToAttack = 0.7;

	if(Battle::Instance()) return;
	Player* player = Game::Instance()->GetPlayer();
	if(_playerInSameRoom && Utils::RandomBool(chanceToAttack)){
		PRINT_BOX(GameStream::SUCCESS_COLOR,
			_name << " attacks you!" << std::endl);
		//Fight(player);
	}
	_playerInSameRoom = player->Location() == _location; 
}

void Alien::BattleAction(const std::vector<FightingActor*>& otherActors){
	static double chanceToFlee = 0.1;
	if(Utils::RandomBool(chanceToFlee)){
		std::string direction = Utils::RandomElement(_location->Directions());
		Run(direction);
	}else{
		Attack(Game::Instance()->GetPlayer());
	}
}

}