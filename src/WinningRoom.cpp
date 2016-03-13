#include "WinningRoom.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(WinningRoom);

void WinningRoom::Update() {
	Game* game = Game::Instance();
	Player* player = game->GetPlayer();
	if(player->Location() == this){
		PRINT_BOX(GameStream::SUCCESS_COLOR,
			_message << std::endl);
		PRINT_BOX(Format::GREEN, 
			"You won the game!" << std::endl);
		game->Quit(std::vector<std::string>());
	}
}


void WinningRoom::SaveImplementation(std::ostream& os) const {
	Room::SaveImplementation(os);
	IO::PrintString(os, _message);
}

void WinningRoom::LoadImplementation(std::istream& is) {
	Room::LoadImplementation(is);
	_message = IO::ReadString(is);
}

}