#include "Entity.hpp"
#include <iostream>
#include <sstream>

using namespace Lab3;

int main(){

	Entity t1("Lol", 1, 2);
	Entity t2;
	std::stringstream ss;
	ss << t1.save();
	std::cout << t1;
	ss >> t2;
	return 0;
}