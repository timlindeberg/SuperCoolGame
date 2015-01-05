#include "Item.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(Item);

Item::Item() {}

Item::Item(std::string name) :
	 	IO(name),
	 	_price(-1), 
	 	_weight(-1) 
	{}

Item::Item(std::string name, unsigned int price, unsigned int weight) :
		 IO(name),
		 _price(price),
		 _weight(weight)
	{}

void Item::SaveImplementation(std::ostream& os) const{
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