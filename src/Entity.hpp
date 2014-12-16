#include "Saveable.hpp"
#include <typeinfo>

namespace Lab3{
	
class Entity : public Saveable {

public:

	Entity() : _type(typeid(*this).name()) {}

	Entity(std::string name, unsigned int price, unsigned int weight) :
		 _type(typeid(*this).name()),
		 _name(name),
		 _price(price),
		 _weight(weight)
	{}

	std::string name() const;
	unsigned int price() const;
	unsigned int weight() const;

	friend std::ostream& operator<<(std::ostream& os, const Entity& e);

protected:

	std::string _name;
	std::string _type;
	unsigned int _price;
	unsigned int _weight;

	virtual void save_impl(std::ostream& os) const override;
	virtual void load_impl(std::istream& os) override;

private:



};
}