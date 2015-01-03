#include "Game.hpp"

using namespace Lab3;

Game* Game::_instance = nullptr;
const std::string Game::_gameFilePath = "./bin/game.txt";

const Game::CommandMap Game::_commandMap(Game::MakeCommandMap());

Game::CommandMap Game::MakeCommandMap() {
	#define GAME_ENTRY(command, function) map[#command] = &Game::function
	Game::CommandMap map;

	GAME_ENTRY(save, SaveGame);
	GAME_ENTRY(load, LoadGame);
	GAME_ENTRY(quit, Quit);

	#undef ENTRY
	return map;
}

// Singleton accessor
Game* Game::Get(){
	if(!Game::_instance){
		Game::_instance = new Game();
	}
	return Game::_instance;
}

Game::Game(){
	LoadGame(_gameFilePath);
}

void Game::Run(){
	_isRunning = true;
	Parser parser;
	while(_isRunning){
		std::string command;
		std::cin >> command;
		prn(command);
		if(ValidCommand(command)){
			pr("valid");
			std::string action;
			std::cin >> action;
			(this->*_commandMap.at(command))(action);
		}else{
			pr("invalid command!");
		}
	}

	prn(_environments.size());
	for(auto& e : _environments){
		pr(*e);
	}
}

bool Game::ValidCommand(const std::string& command){
	return _commandMap.count(command);
}

bool Game::LoadGame(const std::string& fileName){
	std::string file = Utils::FileToString(fileName);
	Utils::Replace(file, '\n', ' ');
	Utils::Replace(file, '\t', ' ');
	std::stringstream ss;
	ss << file;
	ss >> *(this);
	return true;
}

bool Game::SaveGame(const std::string& fileName) {
	std::ofstream file(fileName);
	if(file.is_open()){
		file << Save();
		file.close();
		return true;	
	}
	return false;
}

bool Game::Quit(const std::string& s) {
	_isRunning = false;
	return true;
}

bool Game::IsRunning() const {
	return _isRunning;
}

void Game::SaveImplementation(std::ostream& os) const {
	IO::PrintList(os, _environments);
}

void Game::LoadImplementation(std::istream& is){
	_environments = IO::ParseList<Environment>(is);
	for(auto& e : _environments){
		e->SetUpExits(_environments);
	}
}

#ifndef TEST
int main(){
	Game* game = Game::Get();
	game->Run();
	delete game;

}
#endif

