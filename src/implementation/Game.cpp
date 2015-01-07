#include "Game.hpp"

namespace Lab3{

Game* Game::_instance = nullptr;
const std::string Game::_gameFilePath = "./data/game.txt";
const std::string Game::_savePath = "./saves/";

void Game::InitCommandMap() {
	ENTRY(Game, "save", 	SaveGame, "Saves the game to the specified file.");
	ENTRY(Game, "load", 	LoadGame, "Loads the game from the specified file.");
	ENTRY(Game, "quit", 	Quit, 	  "Exits the game.");
	ENTRY(Game, "help", 	Help, 	  "Prints helpful information.");
	ENTRY(Game, "inspect", 	Inspect,  "Prints a description of an element in the world.");
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
	std::stringstream ss(file);
	LoadImplementation(ss);
}

void Game::Run() {
	_isRunning = true;
	while(_isRunning){
		std::cout << *(GetPlayer()->Location());
		bool goForward = false;
		while(!goForward){
			std::vector<std::string> words = ParseCommand();
			if(words.size() == 0) continue;

			std::string c = words[0];
			bool success = TryCommands(this, words, goForward) ||
						   TryCommands(GetPlayer(), words, goForward);

			if(!success){
				std::cout << COLOR(IO::OVER, CYAN) << std::endl;
				std::cout << COLOR(c, RED) << " is not a valid command! Type " <<
				COLOR("help", YELLOW) << " to see a list of valid commands." << std::endl;
				std::cout << COLOR(IO::UNDER, CYAN) << std::endl;
			}
		}
		for(auto& room : _rooms)
			room->Update();
	}
}

bool Game::TryCommands(Commandable* commandable, std::vector<std::string>& words, bool& goForward){
	std::string c = words[0];
	Result result = commandable->Execute(c, words);
	if(result.HasMessage()){
		std::cout << COLOR(IO::OVER, CYAN) << std::endl;
		std::cout << result.message;
		std::cout << COLOR(IO::UNDER, CYAN) << std::endl;
		goForward = result.goForward;
		return true;
	}
	return false;
}

std::vector<std::string> Game::ParseCommand() const {
	std::string command;

	std::cout << STYLE(COLOR(IO::UNDER, MAGENTA), BOLD) << std::endl;
	std::cout << STYLE(COLOR("> ", MAGENTA), BOLD);

	std::getline(std::cin, command);

	std::cout << STYLE(COLOR(IO::OVER, MAGENTA), BOLD) << std::endl;

	Utils::ToLowerCase(command);
	std::vector<std::string> words = Utils::Split(command);
	return Utils::RemoveBlankWords(words);
} 

//---------------------------------------
// Commands
//---------------------------------------

Actor::Result Game::LoadGame(const std::vector<std::string>& command){
	std::stringstream ss;
	bool goForward = false;
	if(command.size() == 0) {
		ss << COLOR("load", YELLOW) << " needs to be followed by a filename!" << std::endl;
		return Result(ss.str(), false);
	} 

	std::string file = Utils::FileToString(_savePath + command[0]);
	if(file.size() == 0) {
		ss << "No file named " << COLOR(command[0], RED) << std::endl;
	} else {
		Utils::Replace(file, '\n', ' ');
		Utils::Replace(file, '\t', ' ');
		std::stringstream filess;
		filess << file;
		LoadImplementation(filess);
		ss << "Loaded game from file " << COLOR(command[0], GREEN) << std::endl;
		goForward = true;
	}
	return Result(ss.str(), goForward);
}

Actor::Result Game::SaveGame(const std::vector<std::string>& command) {
	std::stringstream ss;
	if(command.size() == 0){
		ss << COLOR("save", YELLOW) << " needs to be followed by a filename!" << std::endl;
		return Result(ss.str(), false);
	}else{
		std::ofstream file(_savePath + command[0]);
		if(file.is_open()){
			SaveImplementation(file);
			file.close();
			ss << "Saved game to file " << COLOR(command[0], GREEN) << std::endl;
		}else{
			ss << "Could not open file";
		}
	}
	
	return Result(ss.str(), false);
}

Actor::Result Game::Quit(const std::vector<std::string>& command) {
	std::stringstream ss;
	ss << "Thanks for playing!" << std::endl;
	_isRunning = false;
	return Result(ss.str(), true);
}

Actor::Result Game::Help(const std::vector<std::string>& command){
	std::stringstream ss;
	if(command.size() == 0){
		ss << "The following commands can be used: " << std::endl;
		std::vector<std::string> commands;
		std::initializer_list<Commandable*> commandables = {this, GetPlayer()};
		for(Commandable* commandable : commandables){
			for(auto iter : commandable->GetCommandMap()){
				std::stringstream commandss;
				commandss << COLOR(iter.first, YELLOW) << " - ";
				commandss << commandable->CommandDescription(iter.first);
				commands.push_back(commandss.str());
			}
		}

		std::sort(commands.begin(), commands.end());
		for(auto& s : commands)
			ss << "\t" << s << std::endl;
	}
	return Result(ss.str(), false);
}

Actor::Result Game::Inspect(const std::vector<std::string>& command){
	std::stringstream ss;
	if(command.size() == 0 || command[0] == "room"){
		ss << *(GetPlayer()->Location());
		return Result(ss.str(), false);
	}

	auto GetDescription = [&ss](const IO& object){
		ss << object.Description() << std::endl;
	};

	std::string object = Utils::Concatenate(command);

	Actor* player = GetPlayer();
	Room* location = player->Location();
	if(Utils::ExecuteOnMatch(player->Items(),    object, GetDescription))
		return Result(ss.str(), false); 
	if(Utils::ExecuteOnMatch(location->Items(),  object, GetDescription))
		return Result(ss.str(), false);    
	if(Utils::ExecuteOnMatch(location->Actors(), object, GetDescription))
		return Result(ss.str(), false); 
		
	ss << "There is nothing named " << COLOR(object, RED) << " here." << std::endl;
	return Result(ss.str(), false);
	
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
	bool playerFound = false;
	for(auto& e : _rooms){
		e->SetUpExits(_rooms);
		if(!playerFound){
			for(auto& a : e->Actors()){
				Player* player = dynamic_cast<Player*>(a.get());
				if(player){
					_player = player;
					playerFound = true;
					break;
				}
			}
		}	
	}

	if(!playerFound){
		std::cerr << "No player found while loading game!" << std::endl;
	}
}

}

int main(){
	Lab3::Game* game = Lab3::Game::Instance();
	game->Run();
	delete game;
}
