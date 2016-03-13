#ifndef LAB3_MEDICAL_BOT
#define LAB3_MEDICAL_BOT

#include "FightingActor.hpp"
#include "Game.hpp"
#include "Player.hpp"

namespace Lab3{

class MedicalBot : public FightingActor {
	
public:

	MedicalBot();

	virtual void Action();
	virtual Actor* Clone() const;

	virtual bool JoinBattle() const;
	virtual void BattleAction(const std::vector<FightingActor*>& otherActors);

protected:

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& is) override;

private:

	void HealActor(FightingActor* fightingActor);

	size_t _healAmount;
	size_t _timeWaited;
	size_t _healsUsed;

	IO_FACTORY_REGISTER_DECL(MedicalBot);
	
};

}

#endif