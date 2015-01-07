#include "Item.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(Item);

Item::Item() {}

void Item::SaveImplementation(std::ostream& os) const {
	os << _price  << ' '; 
	os << _weight << ' '; 
}

void Item::LoadImplementation(std::istream& is){
	is >> _price;
	is >> _weight;
}

unsigned int Item::Price() const {
	return _price;
}

unsigned int Item::Weight() const{
	return _weight;
}

std::ostream& operator<<(std::ostream& os, const Lab3::Item& e){
	os << e.Name() << "(" << e._weight << ", " << e._price << ")";
	return os;
}

}