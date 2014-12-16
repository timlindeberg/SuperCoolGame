#include "Entity.hpp"

using namespace Lab3;

void Entity::save_impl(std::ostream& os) const{
	os << _name << " " << _price << " " << _weight; 
}

void Entity::load_impl(std::istream& is){
	is >> _name;
	is >> _price;
	is >> _weight;
}
