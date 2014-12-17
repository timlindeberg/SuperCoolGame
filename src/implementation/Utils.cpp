#include "Utils.hpp"

std::vector<std::string> Utils::Split(const std::string& s, char delim){
	std::vector<std::string> v;
	std::stringstream ss(s);
	std::string item;
	while(std::getline(ss, item, delim)){
		v.push_back(item);
	}
	return v;
}

// std::string Utils::FileToString(std::ifstream& file){
// 	std::stringstream ss;
// 	ss << file.rdbuf();
// 	return ss.str();
// }
