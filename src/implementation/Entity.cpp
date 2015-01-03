#include "Entity.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(Entity);

Entity::Entity() {}

Entity::Entity(std::string name) :
	 	IO(name),
	 	_price(-1), 
	 	_weight(-1) 
	{}

Entity::Entity(std::string name, unsigned int price, unsigned int weight) :
		 IO(name),
		 _price(price),
		 _weight(weight)
	{}

void Entity::SaveImplementation(std::ostream& os) const{
	os << _price  << ' '; 
	os << _weight << ' '; 
}

void Entity::LoadImplementation(std::istream& is){
	is >> _price;
	is >> _weight;
}

unsigned int Entity::Price() const {
	return _price;
}

unsigned int Entity::Weight() const{
	return _weight;
}

std::ostream& operator<<(std::ostream& os, const Lab3::Entity& e){
	os << e.Name() << "(" << e._weight << ", " << e._price << ")";
}

}