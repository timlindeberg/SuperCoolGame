#ifndef __LAB3__ENTITY__
#define __LAB3__ENTITY__

#include "IO.hpp"
#include <typeinfo>

namespace Lab3{
	
class Entity : public IO {

public:

	Entity();
	Entity(std::string name);
	Entity(std::string name, unsigned int price, unsigned int weight);

	std::string Type() const;
	std::string Name() const;
	unsigned int Price() const;
	unsigned int Weight() const;

	friend std::ostream& operator<<(std::ostream& os, const Entity& e);

protected:

	std::string _name;
	std::string _type;
	unsigned int _price;
	unsigned int _weight;

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& os) override;

private:



};
}

#endif