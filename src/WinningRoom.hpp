#ifndef LAB3__WINNING_ROOM
#define LAB3__WINNING_ROOM

#include "Room.hpp"
#include "Player.hpp"
#include "Game.hpp"

namespace Lab3{

class WinningRoom : public Room {
public:

	virtual void Update() override;

protected:

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& is) override;

private:

	std::string _message;
	
	IO_FACTORY_REGISTER_DECL(WinningRoom);

};

}

#endif