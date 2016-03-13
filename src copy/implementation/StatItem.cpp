#include "StatItem.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(StatItem);

StatItem::StatItem() {}

Item* StatItem::Clone() const {
	return new StatItem(*this);
}

Stats StatItem::GetStats() {
	return _stats;
}

void StatItem::SaveImplementation(std::ostream& os) const {
	Item::SaveImplementation(os);
	os << _stats.Save() << ' ';
}

void StatItem::LoadImplementation(std::istream& is) {
	Item::LoadImplementation(is);
	_stats = IO::ParseStruct<Stats>(is);
}

std::ostream& operator<<(std::ostream& os, const Lab3::StatItem& e){
	os << dynamic_cast<const Lab3::Item&>(e);
	return os << e._stats;
}

}