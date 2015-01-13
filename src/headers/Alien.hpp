#ifndef LAB3_ALIEN
#define LAB3_ALIEN

#include "FightingActor.hpp"
#include "Game.hpp"
#include "Player.hpp"

namespace Lab3{

class Alien : public FightingActor {
public:

	virtual void BattleAction(const std::vector<FightingActor*>& otherActors);

private:

	IO_FACTORY_REGISTER_DECL(Alien);
	
};

}

#endif