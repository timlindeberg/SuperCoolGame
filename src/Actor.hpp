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
	Actor(const Actor& rhs);
	virtual ~Actor();
	virtual Actor* Clone() const = 0;

	Room* Location() const;
	void SetLocation(Room* room);
	
	std::vector<std::unique_ptr<Item>>& Items();
	void AddItem(std::unique_ptr<Item>& item);
	std::unique_ptr<Item> RemoveItem(const std::string& item);

	virtual void Action() = 0;

	// Commands
	bool Go(const std::string& direction);
	virtual void Take(const std::string& itemName);
	virtual void Drop(const std::string& itemName);
	void TalkTo(const std::string& itemName);

	friend std::ostream& operator<<(std::ostream& os, const Actor& e);

protected:

	Room* _location;
	std::vector<std::unique_ptr<Item>> _items;

	bool TryUnlock(const std::string& direction);

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& os) override;

};

}

#endif