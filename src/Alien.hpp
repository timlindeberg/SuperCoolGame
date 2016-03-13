#ifndef LAB3_ALIEN
#define LAB3_ALIEN

#include "FightingActor.hpp"
#include "Game.hpp"
#include "Player.hpp"

namespace Lab3{

class Alien : public FightingActor {
public:

	Alien();

	virtual void Action();
	virtual Actor* Clone() const;

	virtual bool JoinBattle() const;
	virtual void BattleAction(const std::vector<FightingActor*>& otherActors);

private:

	bool _playerInSameRoom;


	IO_FACTORY_REGISTER_DECL(Alien);
	
};

}

#endif