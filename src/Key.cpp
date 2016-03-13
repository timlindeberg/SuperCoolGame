#include "Key.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(Key);

Item* Key::Clone() const{
	return new Key(*this); 
}

}