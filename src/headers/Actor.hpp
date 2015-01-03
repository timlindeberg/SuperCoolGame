#ifndef LAB3_ACTOR
#define LAB3_ACTOR

#include <iostream>
#include <typeinfo>
#include "IO.hpp"

namespace Lab3{
	
class Actor : public IO {

public:
	Actor();
	Actor(std::string name);

	std::string Name() const;
	//virtual void Action() = 0;
	//virtual void Go(int direction) = 0;
	//virtual void Fight(const Actor& actor) = 0;
	//virtual void PickUp() = 0;
	//virtual void Drop() = 0;
	//virtual void TalkTo(const Actor& actor) = 0;

protected:

	std::string _name;

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& os) override;

private:

	IO_FACTORY_REGISTER_DECL(Actor);
};

}

#endif