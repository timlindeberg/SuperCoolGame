#include "HelperBot.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(HelperBot);

HelperBot::HelperBot() : _timeWaited(0) {}

Actor* HelperBot::Clone() const{
	return new HelperBot(*this); 
}

void HelperBot::Action(){
	static const size_t waitTime = 4;

	if(_directions.size() == 0)
		return;

	if(_timeWaited++ <= waitTime)
		return;

	_timeWaited = 0;
	Go(_directions[_directionCount]);
	_directionCount = (_directionCount + 1) % _directions.size();	
}

void HelperBot::SaveImplementation(std::ostream& os) const {
	FriendlyActor::SaveImplementation(os);
	os << _timeWaited << ' ';
	os << _directionCount << ' ';
	IO::PrintStringList(os, _directions);
}

void HelperBot::LoadImplementation(std::istream& is){
	FriendlyActor::LoadImplementation(is);
	is >> _timeWaited;
	is >> _directionCount;
	_directions = IO::ParseStringList(is);

}

}