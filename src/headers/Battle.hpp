#ifndef LAB3_BATTLE
#define LAB3_BATTLE

#include <initializer_list>

#include "Commandable.hpp"
#include "Room.hpp"
#include "GameStream.hpp"
#include "Game.hpp"

namespace Lab3{

class FightingActor;
class Battle {
public:

	static Battle* Instance();
	Battle(FightingActor* actor);
	Battle(const std::initializer_list<FightingActor*>& list);

	void AddActor(FightingActor* actor);
	void RemoveActor(FightingActor* actor);
	std::vector<FightingActor*>& Actors();
	void Start();
	virtual ~Battle();

	void PrintDescription() const;

private:

	static void SetInstance(Battle* battle);
	static Battle* _instance;
	std::vector<FightingActor*> _actors;

};

}

#endif