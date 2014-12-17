#ifndef __LAB3__UTILS__
#define __LAB3__UTILS__

#include <vector>
#include <sstream>

class Utils {

public:
	static std::vector<std::string> Split(const std::string& s, char delim);
	//static std::string FileToString(std::ifstream& file);
};

#endif