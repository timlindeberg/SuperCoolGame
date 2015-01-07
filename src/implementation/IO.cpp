#include "IO.hpp" 

namespace Lab3{

typename IO::Factory::CreationMap* IO::Factory::map = nullptr;

const char IO::DESC_SIGN	= '\"';
const char IO::OBJECT_START	= '[';
const char IO::OBJECT_END	= ']';
const char IO::LIST_START	= '{';
const char IO::LIST_END		= '}';
const char IO::LIST_SEP		= ',';
const char IO::MAP_SEP		= '|';
const std::string IO::UNDER	= "__________________________________________________________________________"; 
const std::string IO::OVER 	= "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾";

// Factory

IO* IO::Factory::CreateInstance(const std::string& className){
	if(!map){
		std::cout << "Class " << className << " is not registered!" << std::endl;
	}

	if(!(*map).count(className)){
		std::cout << "Invalid class name : " << className << std::endl;
	}
	return (*map)[className]();
}

typename IO::Factory::CreationMap* IO::Factory::GetMap(){
	if(!map){
		map = new CreationMap;	
	} 
	return map;
}

// IO

IO::IO() {}
IO::IO(const std::string& name) : _name(name) {}

IO::~IO() {}

const IO& IO::Save() const{
	return static_cast<const IO&>(*this);
}

std::string IO::Type() const{
	int status;
	std::string tmp(abi::__cxa_demangle(typeid(*this).name(),0,0,&status));
	return Utils::Split(tmp, ':')[2];
}

std::string IO::Name() const {
	return _name;
}

const std::string& IO::Description() const {
	return _description;
}

void IO::SetName(const std::string& name){
	_name = name;
}

std::string IO::ReadBetween(std::istream& is, char startSign, char endSign){
	std::string tmp;
	is >> tmp;
	if(tmp[0] != startSign){
		throw std::invalid_argument("Could not read object, missing start sign");
	}

	size_t numStarts = 1;
	std::stringstream ss;
	while(numStarts != 0){
		if(!(is >> tmp)){
			throw std::invalid_argument("Could not parse object, missing end sign");
		}
		if(tmp == " "){
			// Ignore multiple spaces
			continue;
		}
		char c = tmp[0];
		if(c == endSign)
			--numStarts;
		else if(c == startSign)
			++numStarts;

		if(numStarts != 0){
			ss << tmp << ' ';			
		}
	}
	std::string result = ss.str();
	return Utils::Trim(result);
}

std::string IO::ReadObject(std::istream& is){
	return ReadBetween(is, IO::OBJECT_START, IO::OBJECT_END);
}

std::string IO::ReadList(std::istream& is){
	return ReadBetween(is, IO::LIST_START, IO::LIST_END);
}

std::string IO::ReadDescription(std::istream& is){
	return ReadBetween(is, IO::DESC_SIGN, IO::DESC_SIGN);
}

void IO::PrintDescription(std::ostream& os, const std::string description){
	os << IO::DESC_SIGN << ' ';
	os << description << ' ';
	os << IO::DESC_SIGN << ' ';
}

std::ostream& operator<<(std::ostream& os, const Lab3::IO& object){
	os << IO::OBJECT_START << ' ';
	os << object.Type() << ' ';
	os << object._name << ' ';
	IO::PrintDescription(os, object._description);
	object.SaveImplementation(os);
	os << IO::OBJECT_END;
	return os;
}

std::istream& operator>>(std::istream& is, Lab3::IO& object){
	object._description = IO::ReadDescription(is);
	object.LoadImplementation(is);
	return is;
}

}