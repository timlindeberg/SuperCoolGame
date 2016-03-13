#ifndef LAB3_FRIENDLY_ACTOR
#define LAB3_FRIENDLY_ACTOR

#include "FightingActor.hpp"
#include "Game.hpp"
#include "Player.hpp"

namespace Lab3{

class FriendlyActor : public Actor {
public:

	FriendlyActor();

	virtual void Talk();
	virtual void Action();
	virtual Actor* Clone() const;

protected:

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& is) override;

private:

	bool _talked;
	std::vector<std::string> _dialog;

	IO_FACTORY_REGISTER_DECL(FriendlyActor);
	
};

}

#endif