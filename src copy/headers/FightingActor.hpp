#ifndef LAB3_FIGHTING_ACTOR
#define LAB3_FIGHTING_ACTOR

#include <iomanip> 
#include <cmath> 

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

	bool Fled();

	// Commands
	virtual bool Fight(FightingActor* actorToFight);

 	void Attack(FightingActor* opponent);
	void Attack(FightingActor* opponent, const std::string& name);

	bool Run(const std::string& direction);
	bool Run(const std::string& direction, const std::string& name);

	void Use(UsableItem* item);
	void Use(UsableItem* item, const std::string& name);
	
	virtual bool JoinBattle() const = 0;
	virtual void BattleAction(const std::vector<FightingActor*>& otherActors) = 0;

	void PrintBattleDescription();
	
	Stats GetStats() const;

	int HP() const;
	double HPPercentage() const;
	bool IsAlive() const;
	virtual void Kill();
	void TakeDamage(size_t hp, FightingActor* damagedBy);
	void TakeHeal(size_t hp);

protected:

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& os) override;

	bool _fled;
	bool _alive;
	int _currentHP;
	Stats _baseStats;
	Stats _statsFromItems;

private:

	Stats CalculateStatsFromItems() const;


};

}

#endif