#include "Entity.hpp"

using namespace Lab3;

Entity::Entity() : 
	 	_type(typeid(*this).name())
	{}

Entity::Entity(std::string name) :
	 	_type(typeid(*this).name()),
	 	_name(name), _price(-1), 
	 	_weight(-1) 
	{}

Entity::Entity(std::string name, unsigned int price, unsigned int weight) :
		 _type(typeid(*this).name()),
		 _name(name),
		 _price(price),
		 _weight(weight)
	{}

void Entity::SaveImplementation(std::ostream& os) const{
	os << _name << " " << _price << " " << _weight; 
}

void Entity::LoadImplementation(std::istream& is){
	is >> _name;
	is >> _price;
	is >> _weight;
}


std::string Entity::Type() const {
	return _type;
}

std::string Entity::Name() const {
	return _name;
}

unsigned int Entity::Price() const {
	return _price;
}

unsigned int Entity::Weight() const{
	return _weight;
}