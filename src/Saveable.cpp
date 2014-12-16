#include "Saveable.hpp"




namespace Lab3{

const Saveable& Saveable::save() const{
	return static_cast<const Saveable&>(*this);
}

std::ostream& operator<<(std::ostream& os, const Lab3::Saveable& saveable){
	saveable.save_impl(os);
	return os;
}

std::istream& operator>>(std::istream& is, Lab3::Saveable& saveable){
	saveable.load_impl(is);
	return is;
}
}