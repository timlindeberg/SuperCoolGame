#ifndef LAB3__USABLE_ITEM
#define LAB3__USABLE_ITEM

#include "Item.hpp"


namespace Lab3{

class Actor;
class FightingActor;
class UsableItem : public Item {
public:

	virtual Item* Clone() const = 0;
	virtual void Use(FightingActor* user, Actor* enemy = nullptr) = 0;

};

}

#endif