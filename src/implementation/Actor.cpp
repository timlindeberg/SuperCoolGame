#include "Actor.hpp"

using namespace Lab3;

Actor::Actor() : _type(typeid(*this).name()) {}

Actor::Actor(std::string name) : _type(typeid(*this).name()), _name(name) {}

void Actor::SaveImplementation(std::ostream& os) const{
	os << _name;
}

void Actor::LoadImplementation(std::istream& is) {
	is >> _name;
}

std::string Actor::Type() const{
	return _type;
}

std::string Actor::Name() const{
	return _name;
}