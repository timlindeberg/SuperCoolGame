#include "Game.hpp"

using namespace Lab3;

Game* Game::_instance = nullptr;
const std::string Game::_gameFilePath = "./data/game.txt";
const std::string Game::_savePath = "./saves/";

void Game::InitCommandMap() {
	#define ENTRY(name, func) _commandMap[name] = std::bind(&Game::func, this, std::placeholders::_1)
	
	ENTRY("save", SaveGame);
	ENTRY("load", LoadGame);
	ENTRY("quit", Quit);
	ENTRY("help", Help);
	
	#undef ENTRY
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
	InitCommandMap();
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
		std::cout << *(GetPlayer()->Location());
		bool success = false;
		while(!success && _isRunning){
			std::vector<std::string> command = ParseCommand();
			if(command.size() == 0) continue;

			std::string c = command[0];
			if(Execute(this, c, command)) continue;
			success = Execute(GetPlayer(), c, command);
			if(!success){
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
	static std::string under = "____________________________________________________";
	static std::string over  = "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾";
	std::cout << STYLE(COLOR(under, MAGENTA), BOLD) << std::endl;
	std::cout << STYLE(COLOR("> ", MAGENTA), BOLD);
	std::string command;
	std::getline(std::cin, command);
	std::cout << STYLE(COLOR(over, MAGENTA), BOLD) << std::endl;
	Utils::ToLowerCase(command);
	Utils::Trim(command);
	return Utils::Split(command);
} 

bool Game::Execute(Commandable* commandable, const std::string& c, std::vector<std::string>& command){
	if(commandable->IsValidCommand(c)){
		command.erase(command.begin());
		return commandable->GetCommandMap().at(c)(command);
	}
	return false;
}

bool Game::IsValidCommand(const std::string& command) const {
	return _commandMap.count(command);
}

//---------------------------------------
// Commands
//---------------------------------------

bool Game::LoadGame(const std::vector<std::string>& command){
	if(command.size() == 0){
		std::cout << COLOR("load", YELLOW) << " needs to be followed by a filename!" << std::endl;
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
		std::cout << COLOR("save", YELLOW) << " needs to be followed by a filename!" << std::endl;
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
		for(auto iter : this->GetCommandMap())
			commands.push_back(iter.first);
		for(auto iter : GetPlayer()->GetCommandMap())
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

