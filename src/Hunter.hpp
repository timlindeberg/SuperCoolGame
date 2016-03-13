#ifndef LAB3_HUNTER
#define LAB3_HUNTER

#include "FightingActor.hpp"
#include "Game.hpp"
#include "Player.hpp"

namespace Lab3{

class Hunter : public FightingActor {
public:

	Hunter();

	virtual void Action();
	virtual Actor* Clone() const;

	virtual bool JoinBattle() const;
	virtual void BattleAction(const std::vector<FightingActor*>& otherActors);

protected:

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& is) override;

private:

	Room* FindNextRoom() const;

	Room* FindNextRoom(std::map<Room*, Room*>& parentMap) const;
	bool DFS(std::map<Room*, Room*>& parentMap) const;

	size_t _roundsWaited;
	bool _playerInSameRoom;

	IO_FACTORY_REGISTER_DECL(Hunter);
	
};

}

#endif