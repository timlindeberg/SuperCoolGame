#include "Game.hpp"

using namespace Lab3;

Game* Game::_instance = nullptr;
const std::string Game::_gameFilePath = "./data/game.txt";
const std::string Game::_savePath = "./saves/";

const Game::CommandMap Game::_commandMap(Game::MakeCommandMap());

Game::CommandMap Game::MakeCommandMap() {
	_commandMap["save"] = std::bind(&Game::SaveGame, this);
	_commandMap["load"] = &Game::LoadGame;
	_commandMap["quit"] = &Game::Quit;
	_commandMap["help"] = &Game::Help;
}

// Singleton accessor
Game* Game::Instance(){
	if(!Game::_instance){
		Game::_instance = new Game();
	}
	return Game::_instance;
}

Actor* Game::GetPlayer() const {
	return _player;
}

Game::Game() {
	MakeCommandMap();
	std::string file = Utils::FileToString(_gameFilePath);
	Utils::Replace(file, '\n', ' ');
	Utils::Replace(file, '\t', ' ');
	std::stringstream ss;
	ss << file;
	ss >> *(this);
}

void Game::Run(){
	_isRunning = true;
	while(_isRunning){
		std::cout << *(GetPlayer()->Location()) << std::endl;
		bool success = false;
		while(!success){
			std::cout << STYLE(COLOR("> ", MAGENTA), BOLD);
			std::vector<std::string> command = ParseCommand();
			if(command.size() == 0) continue;

			std::string c = command[0];
			if(IsValidCommand(c)){
				command.erase(command.begin());
				success = Execute(c, command);
			}else{
				std::cout << COLOR(command[0], RED) << " is not a valid command! Type " << 
				COLOR("help", YELLOW) << " to see a list of valid commands." << std::endl;
			}
		}
		for(auto& room : _rooms)
			room->Update();
	}
	std::cout << "Thanks for playing!" << std::endl;
}

std::vector<std::string> Game::ParseCommand() const {
	std::string command;
	std::getline(std::cin, command);
	Utils::ToLowerCase(command);
	return Utils::Split(command);
} 

bool Game::Execute(const std::string& c, std::vector<std::string>& command){
	return (this->*_commandMap.at(c))(command);
}

bool Game::IsValidCommand(const std::string& command) const {
	return _commandMap.count(command);
}

//---------------------------------------
// Commands
//---------------------------------------

bool Game::LoadGame(const std::vector<std::string>& command){
	if(command.size() == 0){
		std::cout << COLOR("load", YELLOW) << "-command needs to be followed by a filename!" << std::endl;
		return false;
	}
	std::string file = Utils::FileToString(_savePath + command[0]);
	if(file.size() == 0){
		std::cout << "No file named " << COLOR(command[0], RED) << std::endl;
		return false;
	}
	Utils::Replace(file, '\n', ' ');
	Utils::Replace(file, '\t', ' ');
	std::stringstream ss;
	ss << file;
	ss >> *(this);
	std::cout << "Loaded game from file " << COLOR(command[0], GREEN) << std::endl;
	return true;
}

bool Game::SaveGame(const std::vector<std::string>& command) {
	if(command.size() == 0){
		std::cout << COLOR("save", YELLOW) << "-command needs to be followed by a filename!" << std::endl;
		return false;
	}
	std::ofstream file(_savePath + command[0]);
	if(file.is_open()){
		SaveImplementation(file);
		file.close();
		std::cout << "Saved game to file " << COLOR(command[0], GREEN) << std::endl;
		return true;	
	}
	return false;
}

bool Game::Quit(const std::vector<std::string>& command) {
	_isRunning = false;
	return true;
}

bool Game::Help(const std::vector<std::string>& command){
	if(command.size() == 0){
		std::cout << "The following commands can be used: " << std::endl;
		std::vector<std::string> commands;
		for(auto iter : _commandMap)
			commands.push_back(iter.first);

		std::sort(commands.begin(), commands.end());
		for(auto s : commands)
			std::cout << "\t" << COLOR(s, YELLOW) << std::endl;
	}
	return true;
}

//---------------------------------------
// Private
//---------------------------------------

bool Game::IsRunning() const {
	return _isRunning;
}

void Game::SaveImplementation(std::ostream& os) const {
	IO::PrintList(os, _rooms);
}

void Game::LoadImplementation(std::istream& is){
	_rooms = IO::ParseList<Room>(is);
	for(auto& e : _rooms){
		e->SetUpExits(_rooms);
		for(auto& a : e->GetActors()){
			Player* player = dynamic_cast<Player*>(a.get());
			if(player){
				_player = player;
				break;
			}
		}
	}
}

#ifndef TEST
int main(){
	Game* game = Game::Instance();
	game->Run();
	delete game;

}
#endif

