#include "FriendlyActor.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(FriendlyActor);

FriendlyActor::FriendlyActor() : _talked(0) {}

Actor* FriendlyActor::Clone() const{
	return new FriendlyActor(*this); 
}

void FriendlyActor::Talk() {
	Lab3::out << BeginBox(GameStream::SUCCESS_COLOR);
	Lab3::out << COLOR(_name, BLUE) << " says" << std::endl;
	Lab3::out << Delimiter();
	if(!_talked){
		Lab3::out << "\"" << _dialog[0] << "\"" << std::endl;
		_talked = true;
	}else{
		Lab3::out << "\"" << Utils::RandomElement(_dialog) << "\"" << std::endl;
	}
	Lab3::out << EndBox();
}

void FriendlyActor::Action(){
	// Do nothing
}

void FriendlyActor::SaveImplementation(std::ostream& os) const{
	Actor::SaveImplementation(os);
	os << _talked << ' ';
	IO::PrintStringList(os, _dialog);
}

void FriendlyActor::LoadImplementation(std::istream& is) {
	Actor::LoadImplementation(is);
	is >> _talked;
	_dialog = IO::ParseStringList(is);
}


}