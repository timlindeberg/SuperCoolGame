#include "Player.hpp"
#include "Room.hpp"
#include "Game.hpp"
#include "UsableItem.hpp"

namespace Lab3{

IO_FACTORY_REGISTER_DEF(Player);

void Player::InitCommandMap(){
	using namespace State;
	#define P_ENTRY(name, f, state, desc) ENTRY(Player, name, f, state, desc);

	P_ENTRY("go", 	  	 Go,			NORMAL, "Moves the player to the room in the given direction.");
	P_ENTRY("take", 	 Take, 	 		NORMAL, "Takes a given item." 								  );
	P_ENTRY("drop", 	 Drop, 	 		NORMAL, "Drops a given item." 								  );
	P_ENTRY("fight", 	 Fight, 		NORMAL, "Fight someone." 									  );
	P_ENTRY("inspect", 	 Inspect,   	NORMAL, "Prints a description of an element in the world."	  );
	P_ENTRY("use",		 UseCommand,	NORMAL, "Uses a given item."								  );

	P_ENTRY("use",		 UseCommand,	BATTLE, "Uses a given item."								  );
	P_ENTRY("attack", 	 AttackCommand, BATTLE, "Attack an opponent."	  							  );
	P_ENTRY("run",		 RunCommand,	BATTLE,	"Try to run from the battle."						  );

	P_ENTRY("inventory", Inventory, 	ALL, 	"Prints a list of the players inventory." 			  );
	P_ENTRY("status", 	 Status, 		ALL, 	"Shows the player status."	 						  );

	#undef P_ENTRY
}

Player::Player(){
	InitCommandMap();
}

Player::~Player() {}

void Player::BattleAction(const std::vector<FightingActor*>& otherActors){
	Parser parser;
	Game* game = Game::Instance();
	CommandExecutor commandExecutor(State::BATTLE, { this, game} );
	bool success = false;
	while(!success){
		Battle::Instance()->PrintDescription();
		std::vector<std::string> command = parser.ParseCommand();
		success = commandExecutor.Execute(command);
	}
}

bool Player::AttackCommand(const std::vector<std::string>& command){
	if(command.size() == 0){
		PRINT_BOX(GameStream::FAIL_COLOR,
			"Who do you want to attack?" << std::endl);
		return false;
	}

	std::string actorName = Utils::Concatenate(command);
	FightingActor* opponent = Utils::FindByName(Battle::Instance()->Actors(), actorName);

	if(!opponent){
		PRINT_BOX(GameStream::FAIL_COLOR,
			"There is no one in the battle named " << COLOR(actorName, RED) << "!" << std::endl);
		return false;
	}

	if(opponent == this){
		PRINT_BOX(GameStream::FAIL_COLOR,
					"You cannot attack yourself!" << std::endl);
		return false;
	}

	Attack(opponent, "You");

	return true;	
}

bool Player::RunCommand(const std::vector<std::string>& command){
	std::string direction = Utils::Concatenate(command);
	if(command.size() == 0){
		Lab3::out << BeginBox(GameStream::FAIL_COLOR);
		Lab3::out << COLOR(direction, RED) << 
			"Which direction do you want to run? You can run the following directions" << std::endl;
		Lab3::out << Delimiter();
		Utils::PrintListInColors(Lab3::out, _location->Directions(), { Format::BLUE, Format::CYAN });
		Lab3::out << EndBox();
		return false;
	}

	Room* room = _location->Neighbour(direction);
	if(!room) {
		Lab3::out << BeginBox(GameStream::FAIL_COLOR);
		Lab3::out << COLOR(direction, RED) << 
			" is not a valid direction. You can run the following directions" << std::endl;
		Lab3::out << Delimiter();
		Utils::PrintListInColors(Lab3::out, _location->Directions(), { Format::BLUE, Format::CYAN });
		Lab3::out << EndBox();
		return false;
	}

	Run(room, "You");
	return true;
}

bool Player::UseCommand(const std::vector<std::string>& command){
	if(_items.size() == 0){
		PRINT_BOX(GameStream::FAIL_COLOR,
			"You have no items to use!" << std::endl);
		return false;
	}
	if(command.size() == 0){
		Lab3::out << BeginBox(GameStream::FAIL_COLOR);
		Lab3::out <<  "What item do you want to use? You have the following items" << std::endl;
		Lab3::out << Delimiter();
		Utils::PrintListInColors(Lab3::out, _items, { Format::BLUE, Format::CYAN });
		Lab3::out << EndBox();
		return false;
	}

	std::string itemName = Utils::Concatenate(command);
	Item* item = Utils::FindByName(_items, itemName);

	if(!item){
		PRINT_BOX(GameStream::FAIL_COLOR,
			"You have no item named " << COLOR(itemName, RED) << "!" << std::endl);
		return false;
	}

	UsableItem* usableItem = dynamic_cast<UsableItem*>(item);
	if(!usableItem){
		PRINT_BOX(GameStream::FAIL_COLOR,
			COLOR(itemName, RED) << " can not be used!" << std::endl);
		return false;
	}

	Use(usableItem);
	return true;
}

bool Player::Inventory(const std::vector<std::string>& command){
	Lab3::out << BeginBox(GameStream::SUCCESS_COLOR);
	if(_items.size() == 0){
		Lab3::out << "You have no items." << std::endl;
	}else{
		Lab3::out << "You have the following items" << std::endl;
		Lab3::out << Delimiter();
		Utils::PrintListInColors(Lab3::out, _items, { Format::BLUE, Format::CYAN });
	}
	Lab3::out << EndBox();
	return false;
}

bool Player::Status(const std::vector<std::string>& command) {
	Stats stats = GetStats();
	Lab3::out << BeginBox(GameStream::SUCCESS_COLOR);
	Lab3::out << Alignment::CENTER << "Player status" << std::endl;
	Lab3::out << Delimiter();
	Lab3::out << "Strength: " << COLOR(stats.Strength(), BLUE);
	Lab3::out << ", Agility: " << COLOR(stats.Agility(), BLUE);
	Lab3::out << ", Intelligence: " << COLOR(stats.Intelligence(), BLUE) << std::endl;
	double percent = (double) _currentHP / stats.HP();

	Lab3::out << "HP: " << Utils::PercentColor(percent) << _currentHP <<
		Format::FG_DEFAULT << " / " << COLOR(stats.HP(), GREEN) << std::endl;
	Lab3::out << EndBox();
	return false;
}

bool Player::Inspect(const std::vector<std::string>& command){
	Room* location = Location();
	if(command.size() == 0){
		PRINT_BOX(GameStream::FAIL_COLOR,
			"What do you want to inspect?" << std::endl);
		return false;
	}

	auto PrintDescription = [](const IO& object){
		PRINT_BOX(GameStream::SUCCESS_COLOR,
			object.Description() << std::endl);
	};

	std::string object = Utils::Concatenate(command);

	if(Utils::ExecuteOnMatch(Items(),    		 object, PrintDescription))
		return false; 
	if(Utils::ExecuteOnMatch(location->Items(),  object, PrintDescription))
		return false;    
	if(Utils::ExecuteOnMatch(location->Actors(), object, PrintDescription))
		return false; 
		
	PRINT_BOX(GameStream::FAIL_COLOR,
		"There is nothing named " << COLOR(object, RED) << " here." << std::endl);
	return false;
}

}