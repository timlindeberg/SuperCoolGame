#include "Entity.hpp"
#include "Environment.hpp"
#include <iostream>
#include <sstream>

using namespace Lab3;

int main(){

	Environment e1("hej"), e2("lol"), e3("foo"), e4("bar");
	Entity en1("item1", 1, 2), en2("item2", 2, 3), en3("item3", 3, 4);
	e1.AddExit("North", e2);
	e1.AddExit("West", e3);
	e1.AddExit("South", e4);
	e1.Drop(en1);
	e1.Drop(en2);
	e1.Drop(en3);
	std::cout << e1.Save() << std::endl;
	Environment e5;
	std::stringstream ss;
	ss << e1.Save();
	ss >> e5;
	std::cout << e5.Save() << std::endl;
	return 0;
}