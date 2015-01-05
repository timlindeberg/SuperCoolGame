#ifndef LAB3__UTILS
#define LAB3__UTILS

#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cctype>
#include <initializer_list>

#include "Format.hpp"

class Utils {

public:

	// String utils
	static std::vector<std::string> Split(const std::string& s, char delim = ' ');
	static std::string& Trim(std::string& s);
	static std::string FileToString(const std::string& fileName);
	static std::string& Remove(std::string& s, char c);
	static std::string& Replace(std::string& s, char before, char after);
	static std::string& ToLowerCase(std::string& s);

	// Print utils
	template<class T>
	static void PrintListInColors(std::ostream& os, const std::vector<T>& container,
	 	const std::initializer_list<Format::Code>& colors);

	// Misc
	template<class T>
	static T* Ptr(const std::unique_ptr<T>& obj);

	template<class T>
	static T* Ptr(T& obj);

	template<class T>
	static T* Ptr(T* obj);

private:

	static std::string& LeftTrim(std::string& s);
	static std::string& RightTrim(std::string& s);




};

#include "Utils.tpp"

#endif