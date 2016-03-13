#include "HealingItem.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(HealingItem);

HealingItem::HealingItem() : _healAmount(0) {}


Item* HealingItem::Clone() const{
	return new HealingItem(*this); 
}

void HealingItem::Use(FightingActor* user, Actor* enemy) {
	size_t hp = user->HP();
	user->TakeHeal(_healAmount);
	size_t healedAmount = user->HP() - hp;

	Lab3::out << BeginBox(GameStream::SUCCESS_COLOR);
	Lab3::out << (dynamic_cast<Player*>(user) ? "You" : user->Name()); 
	Lab3::out << " used " << Name() << " and was healed for " 
		<< COLOR(healedAmount, GREEN) << " hp." << std::endl;
	Lab3::out << EndBox();
}

void HealingItem::SaveImplementation(std::ostream& os) const {
	Item::SaveImplementation(os);
	os << _healAmount << ' ';
}

void HealingItem::LoadImplementation(std::istream& is){
	Item::LoadImplementation(is);
	is >> _healAmount;
}

}