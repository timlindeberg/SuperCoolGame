#ifndef LAB3__HEALING_ITEM
#define LAB3__HEALING_ITEM

#include "UsableItem.hpp"
#include "Player.hpp"

namespace Lab3{

class HealingItem : public UsableItem {
public:

	HealingItem();
	Item* Clone() const;

	virtual void Use(FightingActor* user, Actor* enemy = nullptr);

protected:

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& os) override;

private:

	size_t _healAmount;

	IO_FACTORY_REGISTER_DECL(HealingItem);

};

}

#endif