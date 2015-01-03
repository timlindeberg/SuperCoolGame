#include "Actor.hpp"

using namespace Lab3;

IO_FACTORY_REGISTER_DEF(Actor);

Actor::Actor() {}

Actor::Actor(std::string name) : _name(name) {}

void Actor::SaveImplementation(std::ostream& os) const{
}

void Actor::LoadImplementation(std::istream& is) {
}

std::string Actor::Name() const{
	return _name;
}