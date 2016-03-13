#ifndef LAB3_HELPER_BOT
#define LAB3_HELPER_BOT

#include "FightingActor.hpp"
#include "Game.hpp"
#include "Player.hpp"

namespace Lab3{

class HelperBot : public FriendlyActor {
public:

	HelperBot();

	virtual void Action() override;
	virtual Actor* Clone() const;


protected:

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& is) override;

private:

	size_t _timeWaited;
	size_t _directionCount;
	std::vector<std::string> _directions;	

	IO_FACTORY_REGISTER_DECL(HelperBot);

};

}

#endif