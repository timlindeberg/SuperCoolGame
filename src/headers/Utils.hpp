#ifndef LAB3__UTILS
#define LAB3__UTILS

#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>

class Utils {

public:
	static std::vector<std::string> Split(const std::string& s, char delim);
	static std::string& Trim(std::string& s);
	static std::string FileToString(const std::string& fileName);
	static std::string& Remove(std::string& s, char c);
	static std::string& Replace(std::string& s, char before, char after);

private:

	static std::string& LeftTrim(std::string& s);
	static std::string& RightTrim(std::string& s);


};

#endif