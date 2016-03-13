#include "Item.hpp"

namespace Lab3{

Item::Item() : _price(0), _weight(0) {}

void Item::SaveImplementation(std::ostream& os) const {
	os << _name << ' ';
	IO::PrintString(os, _description);
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
	os << e.Name();
	os << COLOR(" ( Price: ", FG_DEFAULT) << COLOR(e._price, YELLOW);
	os << ", Weight: " << COLOR(e._weight, YELLOW) << ")";
	return os;
}

}