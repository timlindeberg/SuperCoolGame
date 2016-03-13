#include "Stats.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(Stats);


Stats::Stats() : _HP(0), _AP(0), _agility(0), _intelligence(0) {}	

size_t Stats::HP() const {
	return _HP;
}

size_t Stats::AP() const {
	return _AP;
}

size_t Stats::Agility() const {
	return _agility;
}

size_t Stats::Intelligence() const{
	return _intelligence;
}

Stats Stats::operator+(const Stats& rhs) const {
	#define ADD(type) newStats.type = type + rhs.type

	Stats newStats;
	ADD(_HP);
	ADD(_AP);
	ADD(_agility);
	ADD(_intelligence);

	#undef ADD
	return newStats;
}

Stats Stats::operator-(const Stats& rhs) const {
	#define SUBTR(type) newStats.type = type - rhs.type

	Stats newStats;
	SUBTR(_HP);
	SUBTR(_AP);
	SUBTR(_agility);
	SUBTR(_intelligence);

	#undef SUBTR
	return newStats;
}

Stats& Stats::operator+=(const Stats& rhs){
	#define ADD_EQ(type) type += rhs.type

	ADD_EQ(_HP);
	ADD_EQ(_AP);
	ADD_EQ(_agility);
	ADD_EQ(_intelligence);

	#undef ADD_EQ
	return *this;
}

Stats& Stats::operator-=(const Stats& rhs){
	#define SUBTR_EQ(type) type -= rhs.type

	SUBTR_EQ(_HP);
	SUBTR_EQ(_AP);
	SUBTR_EQ(_agility);
	SUBTR_EQ(_intelligence);

	#undef SUBTR_EQ
	return *this;
}

void Stats::SaveImplementation(std::ostream& os) const {
	os << _HP << ' ';
	os << _AP << ' ';
	os << _agility << ' ';
	os << _intelligence << ' ';
}

void Stats::LoadImplementation(std::istream& is) {
	is >> _HP;
	is >> _AP;
	is >> _agility;
	is >> _intelligence;
}

std::ostream& operator<<(std::ostream& os, const Lab3::Stats& e){
	os << "HP: " << e._HP;
	os << ", AP: " << e._AP;
	os << ", Agility: " << e._agility;
	os << ", Intelligence: " << e._intelligence;
	return os;
}

}