#ifndef LAB3__KEY
#define LAB3__KEY

#include "Item.hpp"

namespace Lab3{
	
class Key : public Item {

public:

	virtual Item* Clone() const;

private:

	IO_FACTORY_REGISTER_DECL(Key);

};
}

#endif