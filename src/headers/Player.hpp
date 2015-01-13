#ifndef LAB3_PLAYER
#define LAB3_PLAYER

#include "FightingActor.hpp"
#include "Commandable.hpp"
#include "Parser.hpp"
#include "CommandExecutor.hpp"
#include "Battle.hpp"

namespace Lab3{

class Game;

class Player : public FightingActor, public Commandable {
public:
	Player();
	virtual ~Player();

	virtual void BattleAction(const std::vector<FightingActor*>& otherActors) override;

	bool AttackCommand(const std::vector<std::string>& command);
	bool RunCommand(const std::vector<std::string>& command);
	bool UseCommand(const std::vector<std::string>& command);

	virtual bool Inventory(const std::vector<std::string>& command);
	virtual bool Status(const std::vector<std::string>& command);
	virtual bool Inspect(const std::vector<std::string>& command);

private:

	virtual void InitCommandMap() override;
	
	IO_FACTORY_REGISTER_DECL(Player);

};

}

#endif