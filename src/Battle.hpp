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
	virtual ~Battle();

	void Start();
	bool IsRunning() const;
	void End();

	void AddActor(FightingActor* actor);
	void RemoveActor(FightingActor* actor);
	std::vector<FightingActor*>& Actors();

	void PrintString() const;

private:

	static void SetInstance(Battle* battle);
	static Battle* _instance;
	bool _isRunning;
	std::vector<FightingActor*> _actors;

};

}

#endif