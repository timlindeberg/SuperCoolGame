#ifndef LAB3_PLAYER
#define LAB3_PLAYER

#include "FightingActor.hpp"
#include "FriendlyActor.hpp"
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
	virtual Actor* Clone() const;

	virtual void Kill() override;
	virtual bool JoinBattle() const;
	virtual void Action();
	virtual void BattleAction(const std::vector<FightingActor*>& otherActors);

	//Commands

	// Normal
	bool GoCommand(const std::vector<std::string>& command);
	bool UseCommand(const std::vector<std::string>& command);
	bool TakeCommand(const std::vector<std::string>& command);
	bool TalkCommand(const std::vector<std::string>& command);
	bool DropCommand(const std::vector<std::string>& command);
	bool FightCommand(const std::vector<std::string>& command);

	// Battle
	bool AttackCommand(const std::vector<std::string>& command);
	bool RunCommand(const std::vector<std::string>& command);

	// All
	bool Wait(const std::vector<std::string>& command);
	bool Inventory(const std::vector<std::string>& command);
	bool Status(const std::vector<std::string>& command);
	bool Inspect(const std::vector<std::string>& command);

private:

	Parser _parser;
	Parser _battleParser;
	virtual void InitCommandMap() override;
	
	IO_FACTORY_REGISTER_DECL(Player);

};

}

#endif