#include "Stats.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(Stats);


Stats::Stats() : _HP(0), _strength(0), _agility(0), _intelligence(0) {}	

size_t Stats::HP() const {
	return _HP;
}

size_t Stats::Strength() const {
	return _strength;
}

size_t Stats::Agility() const {
	return _agility;
}

size_t Stats::Intelligence() const{
	return _intelligence;
}

Stats Stats::operator+(const Stats& rhs){
	#define ADD(type) newStats.type = type + rhs.type

	Stats newStats;
	ADD(_HP);
	ADD(_strength);
	ADD(_agility);
	ADD(_intelligence);

	#undef ADD
	return newStats;
}

Stats Stats::operator-(const Stats& rhs){
	#define SUBTR(type) newStats.type = type - rhs.type

	Stats newStats;
	SUBTR(_HP);
	SUBTR(_strength);
	SUBTR(_agility);
	SUBTR(_intelligence);

	#undef SUBTR
	return newStats;
}

Stats& Stats::operator+=(const Stats& rhs){
	#define ADD_EQ(type) type += rhs.type

	ADD_EQ(_HP);
	ADD_EQ(_strength);
	ADD_EQ(_agility);
	ADD_EQ(_intelligence);

	#undef ADD_EQ
	return *this;
}

Stats& Stats::operator-=(const Stats& rhs){
	#define SUBTR_EQ(type) type -= rhs.type

	SUBTR_EQ(_HP);
	SUBTR_EQ(_strength);
	SUBTR_EQ(_agility);
	SUBTR_EQ(_intelligence);

	#undef SUBTR_EQ
	return *this;
}

void Stats::SaveImplementation(std::ostream& os) const {
	os << _HP << ' ';
	os << _strength << ' ';
	os << _agility << ' ';
	os << _intelligence << ' ';
}

void Stats::LoadImplementation(std::istream& is) {
	is >> _HP;
	is >> _strength;
	is >> _agility;
	is >> _intelligence;
}

std::ostream& operator<<(std::ostream& os, const Lab3::Stats& e){
	os << "HP: " << e._HP;
	os << ", Strength: " << e._strength;
	os << ", Agility: " << e._agility;
	os << ", Intelligence: " << e._intelligence;
	return os;
}

}