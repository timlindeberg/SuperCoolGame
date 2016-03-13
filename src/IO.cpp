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

IO::IO() : _name(""), _description("") {}

IO::IO(const std::string& name, const std::string& description) : 
	_name(name), 
	_description(description) 
{}

IO::~IO() {}

const IO& IO::Save() const{
	return static_cast<const IO&>(*this);
}

std::string IO::Type() const{
	int status;
	char* str = abi::__cxa_demangle(typeid(*this).name(), 0, 0, &status);
	std::string result(str);
	free(str);
	return Utils::Split(result, ':')[2];
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
    //prn(tmp);
    if(tmp[0] != startSign){
        throw std::invalid_argument("Could not read object, missing start sign");
    }
	size_t numStarts = 1;
	std::stringstream ss;
	while(numStarts != 0){
		if(!(is >> tmp)){
			std::string error = "Could not parse object, missing end sign:";
			error.append(1, endSign);
			throw std::invalid_argument(error);
		}

		if(tmp == " ")
			continue;

		char c = tmp[0];
		if(c == endSign)
			--numStarts;
		else if(c == startSign)
			++numStarts;

		if(numStarts != 0){
			ss << ' ';
			ss << tmp;			
		}
	}
	std::string result = ss.str();
	return Utils::Trim(result);
}

std::string IO::ReadObject(std::istream& is){
	//pr("Reading object.");
	return ReadBetween(is, IO::OBJECT_START, IO::OBJECT_END);
}

std::string IO::ReadList(std::istream& is){
	//pr("Reading list.");
	return ReadBetween(is, IO::LIST_START, IO::LIST_END);
}

std::vector<std::string> IO::ParseStringList(std::istream& is){
	//pr("Parsing list of type string");
	std::stringstream ss;
	ss << ReadList(is);
	std::vector<std::string> v;
	if(ss.str() == ""){
		// Empty list
		return v;
	}

 	std::string tmp;
    do{
		std::string str = IO::ReadString(ss);
       	v.push_back(str);
    }while((ss >> tmp) && tmp[0] == IO::LIST_SEP);
	return v;
}

void IO::PrintStringList(std::ostream& os, const std::vector<std::string>& list){
	size_t N = list.size();
	if (N == 0){
		os << IO::LIST_START << ' ' << IO::LIST_END << ' ';
		return;
	}

	os << IO::LIST_START << ' ';
	for(size_t i = 0; i < N - 1; ++i){
		IO::PrintString(os, list[i]);
		os << ' ' << IO::LIST_SEP << ' ';
	}
	IO::PrintString(os, list[N - 1]);
	os << ' ';
	os << IO::LIST_END << ' ';
}

std::string IO::ReadString(std::istream& is){
	//pr("Reading description.");
	char c;
	is >> c;
	if(c != '"'){
		throw std::invalid_argument("Could not read description of, missing start sign : '\"'");
	}
	std::string description;
	std::getline(is, description, '"');
	//pr("\tResult: " << description);
	return Utils::Trim(description);
}

void IO::PrintString(std::ostream& os, const std::string description){
	os << IO::DESC_SIGN;
	os << description;
	os << IO::DESC_SIGN << ' ';
}

std::ostream& operator<<(std::ostream& os, const Lab3::IO& object){
	os << IO::OBJECT_START << ' ';
	os << object.Type() << ' ';
	object.SaveImplementation(os);
	os << IO::OBJECT_END;
	return os;
}

std::istream& operator>>(std::istream& is, Lab3::IO& object){
	//pr("Loading object: " << object.Name());
	object.LoadImplementation(is);
	return is;
}

}