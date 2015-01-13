#include "Game.hpp"
#include "Room.hpp"
#include "Player.hpp"

namespace Lab3{

Game* Game::_instance = nullptr;
const std::string Game::_gameFilePath = "./data/game.save";
const std::string Game::_savePath = "./saves/";
const std::string Game::_saveExtension = ".save";

void Game::InitCommandMap() {
	using namespace State;
	#define G_ENTRY(name, f, state, desc) ENTRY(Game, name, f, state, desc);

	G_ENTRY("new",  NewGame,  INTRO,  "Starts a new game."					 	);
	G_ENTRY("save", SaveGame, NORMAL, "Saves the game to the specified file." 	);
	G_ENTRY("load", LoadGame, NORMAL, "Loads the game from the specified file." );
	G_ENTRY("load", LoadGame, INTRO,  "Loads the game from the specified file." );
	G_ENTRY("quit", Quit, 	  ALL,	  "Exits the game." 						);

	#undef G_ENTRY
}

// Singleton accessor
Game* Game::Instance(){
	if(!Game::_instance){
		Game::_instance = new Game();
	}
	return Game::_instance;
}


bool Game::IsRunning() const {
	return _isRunning;
}

Player* Game::GetPlayer() const {
	return _player;
}

State::Value Game::State() const {
	return _currentState;
}

Game::Game() {
	InitCommandMap();
	_player = nullptr;
}

void Game::Run() {
	_isRunning = true;
	Introduction();
	if(!_isRunning) return;

	Parser parser;
	CommandExecutor commandExecutor(State::NORMAL, { this, GetPlayer() });
	GetPlayer()->Location()->PrintDescription();
	while(_isRunning){
		std::vector<std::string> command = parser.ParseCommand();

		commandExecutor.Execute(command);
		if(_isRunning){
			GetPlayer()->Location()->PrintDescription();
			for(auto& room : _rooms)
				room->Update();
		}
	}
}


void Game::Introduction(){
	// static std::regex regex("(\033\\[(\\d*)m)");
	// static std::string compare = "\033";
	// static std::string empty;
	// std::stringstream ss;
	// ss << "Type " << COLOR("new", YELLOW) << " to start a new game " <<
	// 	"or type " << COLOR("load", YELLOW) << " <gamefile> to load a game!" << std::endl;

	// std::string word = ss.str();
	// std::string ansiremoved;
	// std::smatch sm;
	// std::sregex_token_iterator begin(word.begin(), word.end(), regex, 1	);
	// std::sregex_token_iterator end;
	// for(; begin != end; ++begin){
	// 	std::cout << "[" <<  begin->first - word.begin() << ", " << begin->second - word.begin() << "]" <<std::endl;
	// 	//Format::Code color = static_cast<Format::Code>(std::stoi((*begin).str()));
	// 	//std::cout << color << "color" << Format::FG_DEFAULT << std::endl;

	// }
	// if(word.find(compare) != std::string::npos){
	// 	std::regex_search(word, sm, regex);
	// 	ansiremoved = std::regex_replace(word, regex, empty);
	// }
	
	// size_t pos = sm.position(0);
	// size_t length = sm.length(0);
	// //pr("[" << pos << ", " << pos + length << "]: " << sm[0].str());	

	// INTRO TEXTs
	Lab3::out << BeginBox(Format::CYAN);
	Lab3::out << Alignment::CENTER << "Welcome to Super cool game! " << std::endl;
	Lab3::out << Delimiter();
	Lab3::out << "Type " << COLOR("new", YELLOW) << " to start a new game " <<
		"or type " << COLOR("load", YELLOW) << " <gamefile> to load a game!" << std::endl;
	Lab3::out << "You can always type " << COLOR("help", YELLOW) << 
		" if you are unsure which commands can be used!" << std::endl;
	Lab3::out << EndBox();

	Parser parser;
	CommandExecutor commandExecutor(State::INTRO, this); 
	bool success = false;

	while(!success){
		std::vector<std::string> command = parser.ParseCommand();
		success = commandExecutor.Execute(command);
	}
}

//---------------------------------------
// Commands
//---------------------------------------

bool Game::NewGame(const std::vector<std::string>& command){
	std::string file = Utils::FileToString(_gameFilePath);
	Utils::Replace(file, '\n', ' ');
	Utils::Replace(file, '\t', ' ');
	std::stringstream ss(file);
	LoadImplementation(ss);
	return true;
}

bool Game::LoadGame(const std::vector<std::string>& command){
	if(command.size() == 0) {
		PRINT_BOX(GameStream::FAIL_COLOR,
		 	COLOR("load", YELLOW) << " needs to be followed by a filename!" << std::endl);
		return false;
	} 

	std::string file = Utils::FileToString(_savePath + command[0] + _saveExtension);
	if(file.size() == 0) {
		PRINT_BOX(GameStream::FAIL_COLOR,
			"No file named " << COLOR(command[0], RED) << std::endl);
		return false;
	}
	Utils::Replace(file, '\n', ' ');
	Utils::Replace(file, '\t', ' ');
	std::stringstream ss;
	ss << file;
	LoadImplementation(ss);
	PRINT_BOX(GameStream::SUCCESS_COLOR, 
		"Loaded game from file " << COLOR(command[0], GREEN) << std::endl);

	return true;
}

bool Game::SaveGame(const std::vector<std::string>& command) {
	if(command.size() == 0){
		PRINT_BOX(GameStream::FAIL_COLOR,
			COLOR("save", YELLOW) << " needs to be followed by a filename!" << std::endl);
		return false;
	}
	std::string fileName = Utils::Concatenate(command);
	std::ofstream file(_savePath + fileName + _saveExtension);
	if(file.is_open()){
		SaveImplementation(file);
		file.close();
		PRINT_BOX(GameStream::SUCCESS_COLOR,
			"Saved game to file " << COLOR(fileName, GREEN) << std::endl);
	}else{
		PRINT_BOX(GameStream::FAIL_COLOR,
			"Could not open file" << COLOR(fileName, RED) << std::endl);
	}
	
	return false;
}

bool Game::Quit(const std::vector<std::string>& command) {
	PRINT_BOX(GameStream::SUCCESS_COLOR,
		"Thanks for playing!" << std::endl);
	_isRunning = false;
	return true;
}


//---------------------------------------
// Private
//---------------------------------------

void Game::SaveImplementation(std::ostream& os) const {
	IO::PrintList(os, _rooms);
}

void Game::LoadImplementation(std::istream& is){
	try{
		_rooms = IO::ParseList<Room>(is);
	}catch(std::invalid_argument& e){
		std::cerr << COLOR(e.what(), RED) << std::endl;;	
		_isRunning = false;
		return;
	}
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
