#ifndef LAB3_ACTOR
#define LAB3_ACTOR

#include <iostream>
#include <typeinfo>

#include "IO.hpp"
#include "Format.hpp"
#include "Item.hpp"

namespace Lab3{

class Room;
class Actor : public IO {

public:

	Actor();
	Actor(std::string name);

	Room* Location() const;
	void SetLocation(Room* room);
	std::vector<std::unique_ptr<Item>>& Items();
	void AddItem(std::unique_ptr<Item>& item);
	
	// Commands
	virtual bool Go(const std::vector<std::string>& command);
	virtual bool Take(const std::vector<std::string>& command);
	virtual bool Drop(const std::vector<std::string>& command);
	virtual bool TalkTo(const std::vector<std::string>& command);
	virtual bool Use(const std::vector<std::string>& command);

protected:

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& os) override;

private:

	Room* _location;
	std::vector<std::unique_ptr<Item>> _items;

	IO_FACTORY_REGISTER_DECL(Actor);
};

}

#endif