#include "Actor.hpp"

using namespace Lab3;

Actor::Actor() : _type(typeid(*this).name()) {}

Actor::Actor(std::string name) : _type(typeid(*this).name()), _name(name) {}

void Actor::save_impl(std::ostream& os) const{
	os << _name;
}

void Actor::load_impl(std::istream& is) {
	is >> _name;
}

std::string Actor::type() const{
	return _type;
}

std::string Actor::name() const{
	return _name;
}