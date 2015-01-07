#ifndef LAB3_ACTOR
#define LAB3_ACTOR

#include <iostream>
#include <typeinfo>

#include "IO.hpp"
#include "Commandable.hpp"
#include "Format.hpp"
#include "Item.hpp"

namespace Lab3{

class Room;
class Actor : public IO, public Commandable {

public:

	Actor();
	virtual ~Actor();
	
	Room* Location() const;
	void SetLocation(Room* room);
	
	std::vector<std::unique_ptr<Item>>& Items();
	void AddItem(std::unique_ptr<Item>& item);
	std::unique_ptr<Item> RemoveItem(const std::string& item);

	// Commands
	virtual Result Go(const std::vector<std::string>& command);
	virtual Result Take(const std::vector<std::string>& command);
	virtual Result Drop(const std::vector<std::string>& command);
	virtual Result TalkTo(const std::vector<std::string>& command);
	virtual Result Use(const std::vector<std::string>& command);
	virtual Result Inventory(const std::vector<std::string>& command);

protected:

	Room* _location;
	std::vector<std::unique_ptr<Item>> _items;

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& os) override;

private:

	virtual void InitCommandMap() override;

	IO_FACTORY_REGISTER_DECL(Actor);
};

}

#endif