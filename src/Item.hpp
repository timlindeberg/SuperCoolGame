#ifndef LAB3__ITEM
#define LAB3__ITEM

#include "IO.hpp"

namespace Lab3{
	
class Item : public IO {

public:

	Item();

	virtual Item* Clone() const = 0;

	unsigned int Price() const;
	unsigned int Weight() const;

	friend std::ostream& operator<<(std::ostream& os, const Item& e);

protected:

	unsigned int _price;
	unsigned int _weight;

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& is) override;

private:

};
}

#endif