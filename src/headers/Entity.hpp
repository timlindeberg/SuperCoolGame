#ifndef LAB3__ENTITY
#define LAB3__ENTITY

#include "IO.hpp"
#include <typeinfo>

namespace Lab3{
	
class Entity : public IO {

public:

	Entity();
	Entity(std::string name);
	Entity(std::string name, unsigned int price, unsigned int weight);

	unsigned int Price() const;
	unsigned int Weight() const;

	friend std::ostream& operator<<(std::ostream& os, const Entity& e);

protected:

	unsigned int _price;
	unsigned int _weight;

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& os) override;

private:

	IO_FACTORY_REGISTER_DECL(Entity);

};
}

#endif