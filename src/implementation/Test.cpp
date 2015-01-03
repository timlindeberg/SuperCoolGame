#include "Entity.hpp"
#include "Environment.hpp"
#include <iostream>
#include <sstream>
#include <typeinfo>

using namespace Lab3;


int main(){

	pr("START!");
	std::stringstream ss("[ Environment foo \" You are standing in a stuff \" { } { } { } ]");
	std::unique_ptr<Environment> e1 = IO::ParseObject<Environment>(ss);
	
	pr(e1->Save());

	return 0;
}