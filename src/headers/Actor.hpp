#ifndef LAB3_ACTOR
#define LAB3_ACTOR

#include <iostream>
#include <typeinfo>

#include "IO.hpp"
#include "Format.hpp"
#include "Item.hpp"
#include "GameStream.hpp"

namespace Lab3{

class Room;
class Actor : public IO {

public:

	Actor();
	virtual ~Actor();
	
	Room* Location() const;
	void SetLocation(Room* room);
	
	std::vector<std::unique_ptr<Item>>& Items();
	void AddItem(std::unique_ptr<Item>& item);
	std::unique_ptr<Item> RemoveItem(const std::string& item);

	// Commands
	virtual bool Go(const std::vector<std::string>& command);
	virtual bool Take(const std::vector<std::string>& command);
	virtual bool Drop(const std::vector<std::string>& command);
	virtual bool TalkTo(const std::vector<std::string>& command);

	friend std::ostream& operator<<(std::ostream& os, const Actor& e);

protected:

	Room* _location;
	std::vector<std::unique_ptr<Item>> _items;

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& os) override;

private:

	IO_FACTORY_REGISTER_DECL(Actor);
};

}

#endif