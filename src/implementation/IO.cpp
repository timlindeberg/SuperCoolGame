#include "IO.hpp"

namespace Lab3{

const char IO::OBJECT_SEP 	  = '%';
const char IO::LIST_SEP       = '#';
const char IO::MAP_SEP        = '|';

const IO& IO::Save() const{
	return static_cast<const IO&>(*this);
}

std::string IO::ReadObject(std::istream& is){
	std::string tmp;
	is >> tmp;
	if(tmp[0] != IO::OBJECT_SEP){
		throw std::invalid_argument("Could not parse stuff, invalid formatting!");
	}
	std::stringstream ss;
	while(is >> tmp && tmp[0] != IO::OBJECT_SEP){
		ss << tmp;
	}
	return ss.str();
}

std::vector<std::string> IO::ReadList(std::istream& is){
	std::vector<std::string> v;
	std::string tmp;
	is >> tmp;
	if(tmp[0] != IO::LIST_SEP){
		throw std::invalid_argument("Could not parse stuff, invalid formatting!");
	}

	while(is >> tmp && tmp[0] != IO::OBJECT_SEP){
		v.push_back(tmp);
	}
	return v;
}

std::ostream& operator<<(std::ostream& os, const Lab3::IO& saveable){
	saveable.SaveImplementation(os);
	return os;
}

std::istream& operator>>(std::istream& is, Lab3::IO& saveable){
	saveable.LoadImplementation(is);
	return is;
}
}