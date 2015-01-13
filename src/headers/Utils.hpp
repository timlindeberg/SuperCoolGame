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
#include <memory>
#include <regex>
#include <random>

#include "Format.hpp"

// Temporary print macros for debugging
#define pr(a) std::cout << a << std::endl
#define prn(a) std::cout << #a << ": " << a << std::endl
#define prv(a)  { 												\
					for(size_t i = 0; i < a.size(); ++i){		\
						std::cout << i << ": " << a[i] << " ";	\
					}											\
					std::cout << std::endl;						\
				}												\


class Utils {

public:

	// String utils
	static std::vector<std::string> Split(const std::string& s, char delim = ' ');
	static std::string Concatenate(const std::vector<std::string>& v);
	static std::string& Trim(std::string& s);
	static std::string FileToString(const std::string& fileName);
	static std::string& Remove(std::string& s, char c);
	static std::string& Replace(std::string& s, char before, char after);
	static std::string& ToLowerCase(std::string& s);
	static std::vector<std::string>& RemoveBlankWords(std::vector<std::string>& v);
	static std::string& RemoveAnsiFormating(std::string& s);
	static size_t PrintSize(std::string s);
	static size_t Count(const std::string& s, char c);
	static bool AllWhitespace(const std::string& s);

	// Game utils

	template<class T>
	static T* FindByName(const std::vector<std::unique_ptr<T>>& container, const std::string& name);
	template<class T>
	static T* FindByName(const std::vector<T*>& container, const std::string& name);


	template<class T, class U>
	static bool SameName(const T& t, const U& u);

	template<class T>
	static bool SameName(const T& t, const std::string& name);

	template<class T>
	static void AddItem(std::vector<std::unique_ptr<T>>& container, std::unique_ptr<T>& ptr);

	template<class T>
	static std::unique_ptr<T> RemoveItem(std::vector<std::unique_ptr<T>>& container, const std::string& name);

	// Print utils
	template<class Stream, class T>
	static void PrintListInColors(Stream& out, const std::vector<T>& container,
	 	const std::initializer_list<Format::Code>& colors = { Format::FG_DEFAULT });

	template<class T, typename Func>
	static bool ExecuteOnMatch(const std::vector<T>& objects, const std::string& name, Func f);

	static Format::Code PercentColor(double percentage); 

	// Random numbers
	static int NormalDistInt(double mean, double stdDev);
	static int RandomInt(double min, double max);
	static float RandomFloat(float min = 0, float max = 1);
	static bool RandomBool(double probability);

	template<class T>
	static T& RandomElement(std::vector<T> v);

	static uint32_t seed;
	static std::random_device rd;
	static std::mt19937 RNG;


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