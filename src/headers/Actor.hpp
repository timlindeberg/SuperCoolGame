#ifndef __LAB3__ACTOR__
#define __LAB3__ACTOR__

#include <iostream>
#include <typeinfo>
#include "IO.hpp"

namespace Lab3{
	
class Actor : public IO {

public:
	Actor();
	Actor(std::string name);

	std::string Type() const;
	std::string Name() const;
	virtual void Action() = 0;
	virtual void Go(int direction) = 0;
	virtual void Fight(const Actor& actor) = 0;
	virtual void PickUp() = 0;
	virtual void Drop() = 0;
	virtual void TalkTo(const Actor& actor) = 0;

protected:

	std::string _type;
	std::string _name;

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& os) override;

private:

};

}

#endif