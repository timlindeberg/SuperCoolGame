#ifndef LAB3_STATS
#define LAB3_STATS

#include "IO.hpp"

namespace Lab3{

class Stats : public IO {
public:

	Stats();

	size_t HP() const;
	size_t Strength() const;
	size_t Agility() const;
	size_t Intelligence() const;

	Stats operator+(const Stats& rhs);
	Stats operator-(const Stats& rhs);
	Stats& operator+=(const Stats& rhs);
	Stats& operator-=(const Stats& rhs);

	friend std::ostream& operator<<(std::ostream& os, const Stats& e);

protected:
	
	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& os) override;

private:

	size_t _HP;
	size_t _strength;
	size_t _agility;
	size_t _intelligence;

	IO_FACTORY_REGISTER_DECL(Stats);

};

}

#endif