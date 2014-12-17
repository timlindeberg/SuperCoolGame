#include "Game.hpp"

using namespace Lab3;

Game* Game::_instance = nullptr;

// Singleton accessor
Game* Game::Instance(){
	if(!Game::_instance){
		Game::_instance = new Game();
	}
	return Game::_instance;
}

Game::Game(){

}

void Game::Run(){
	_isRunning = true;
	while(_isRunning){
		// Do stuff
	}

}

bool Game::LoadGame(const std::string& fileName){
	std::ifstream file(fileName);
	if(file.is_open()){
		file >> *(this);
		file.close();
		return true;
	}
	return false;
}

bool Game::SaveGame(const std::string& fileName) const{
	std::ofstream file(fileName);
	if(file.is_open()){
		file << Save();
		file.close();
		return true;	
	}
	return false;
}

bool Game::IsRunning() const{
	return _isRunning;
}

void Game::SaveImplementation(std::ostream& os) const{
	os << IO::OBJECT_SEP << ' ';
	os << IO::LIST_SEP << ' ';
	for(const Environment& env : _environments){
		os << env.Save();
	}
	os << IO::LIST_SEP << '\n';
	os << IO::LIST_SEP << ' ';
	for(const Entity& ent : _entities){
		os << ent.Save();
	}
	os << IO::LIST_SEP << '\n';
	os << IO::LIST_SEP << ' ';
	for(const Actor& act : _actors){
		os << act.Save();
	}
	os << IO::LIST_SEP << '\n';
	os << IO::OBJECT_SEP << ' ';
}

void Game::LoadImplementation(std::istream& is){
	std::vector<Environment> environments;
	std::vector<Entity> entitys;
	std::vector<Actor> actors;
	std::string tmp;

	is >> tmp;

}

#ifndef TEST
int main(){
	Game* game = Game::Instance();
	game->Run();
	delete game;

}
#endif

