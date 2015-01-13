#ifndef LAB3_FIGHTING_ACTOR
#define LAB3_FIGHTING_ACTOR

#include "Stats.hpp"
#include "StatItem.hpp"
#include "Actor.hpp"
#include "Game.hpp"

namespace Lab3{

class UsableItem;
class Room;
class Battle;
class FightingActor : public Actor {
public:

	FightingActor();
	virtual ~FightingActor();

	// Commands
	virtual bool Fight(const std::vector<std::string>& command);

 	void Attack(FightingActor* opponent);
	void Attack(FightingActor* opponent, const std::string& name);

	void Run(Room* room);
	void Run(Room* room, const std::string& name);

	void Use(UsableItem* item);
	void Use(UsableItem* item, const std::string& name);
	
	virtual void BattleAction(const std::vector<FightingActor*>& otherActors) = 0;

	void PrintBattleDescription();
	
	Stats GetStats();

	int HP() const;
	virtual bool IsAlive() const;
	virtual void Kill(FightingActor* killedBy);
	virtual void TakeDamage(size_t hp, FightingActor* killedBy);
	virtual void TakeHeal(size_t hp);

protected:

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& os) override;

	bool _alive;
	int _currentHP;
	Stats _baseStats;
	Stats _statsFromItems;

private:

	virtual Stats CalculateStatsFromItems();


};

}

#endif