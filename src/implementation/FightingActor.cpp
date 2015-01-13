#include "FightingActor.hpp"
#include "Room.hpp"
#include "Battle.hpp"
#include "UsableItem.hpp"

namespace Lab3{

FightingActor::FightingActor() {}

FightingActor::~FightingActor() {}

//TEMP

Stats FightingActor::GetStats() {
	return _baseStats + _statsFromItems;
}

bool FightingActor::Fight(const std::vector<std::string>& command){
	if(command.size() == 0){
		PRINT_BOX(GameStream::FAIL_COLOR,
			"Who do you want to fight?" << std::endl);
		return false;
	}
	std::string actorName = Utils::Concatenate(command);
	Actor* actor = Utils::FindByName(_location->Actors(), actorName);
	if(!actor){
		PRINT_BOX(GameStream::FAIL_COLOR,
					"There is no one here named " << COLOR(actorName, RED) << std::endl);
		return false;
	}
	FightingActor* fightingActor = dynamic_cast<FightingActor*>(actor);
	if(!fightingActor){
		PRINT_BOX(GameStream::FAIL_COLOR,
			"You can not fight " << COLOR(actorName, RED) << "!" << std::endl);
		return false;
	}

	if(dynamic_cast<Player*>(fightingActor)){
		PRINT_BOX(GameStream::FAIL_COLOR,
					"You cannot fight yourself!" << std::endl);
		return false;
	}

	Battle battle({ Game::Instance()->GetPlayer(), fightingActor });
	battle.Start();
	return true;
}

void FightingActor::Attack(FightingActor* opponent){
	Attack(opponent, _name);
}

void FightingActor::Attack(FightingActor* opponent, const std::string& name){
	if(Utils::RandomBool(0.1)){
		PRINT_BOX(GameStream::SUCCESS_COLOR,
			name << " missed!" << std::endl);
		return;
	}

	Stats stats = GetStats();
	size_t damage = Utils::NormalDistInt(stats.Strength(), 0.5);

	PRINT_BOX(GameStream::SUCCESS_COLOR,
		name << " attacked " << COLOR(opponent->Name(), BLUE) << " for " << 
		COLOR(damage, RED) << " damage." << std::endl);

	opponent->TakeDamage(damage, this);
}

void FightingActor::Run(Room* room){
	Run(room, _name);
}

void FightingActor::Run(Room* room, const std::string& name){
	if(Utils::RandomBool(0.5)){
		PRINT_BOX(GameStream::SUCCESS_COLOR,
			name << " tried to flee but failed!" << std::endl);
		return;		
	}

	Battle::Instance()->RemoveActor(this);
	std::unique_ptr<Actor> actor = _location->RemoveActor(this);
	room->AddActor(actor);
	_location = room;

	PRINT_BOX(GameStream::SUCCESS_COLOR,
			name << " managed to flee!" << std::endl);
}

void FightingActor::Use(UsableItem* item){
	Use(item, _name);
}

void FightingActor::Use(UsableItem* item, const std::string& name){
	item->Use(this);
	Utils::RemoveItem(_items, item->Name());
}

int FightingActor::HP() const {
	return _currentHP;
}

bool FightingActor::IsAlive() const {
	return _alive;
}

void FightingActor::TakeDamage(size_t damage, FightingActor* damagedBy){
	_currentHP -= damage;
	if(_currentHP <= 0){
		Kill(damagedBy);
	}
}

void FightingActor::Kill(FightingActor* killedBy) {
	Lab3::out << BeginBox(GameStream::SUCCESS_COLOR);
	Lab3::out << COLOR(_name, BLUE) << " was ";
	Lab3::out << COLOR("killed", RED) << " by ";
	Lab3::out << COLOR(killedBy->Name(), BLUE) << "!" << std::endl;
	Lab3::out << EndBox();
	Battle* battle = Battle::Instance();
	if(battle){
		battle->RemoveActor(this);
	}
	_location->RemoveActor(this);
}

void FightingActor::TakeHeal(size_t heal){
	_currentHP += heal;
	int max = _baseStats.HP() + _statsFromItems.HP();
	if(_currentHP >= max)
		_currentHP = max;
}

void FightingActor::PrintBattleDescription(){
	Lab3::out << COLOR(_name, CYAN) << std::endl;
	Stats stats = GetStats();
	double percent = (double)_currentHP / stats.HP();
	Lab3::out << "HP " << Utils::PercentColor(percent) <<
		 _currentHP << Format::FG_DEFAULT << " / " << COLOR(stats.HP(), GREEN) << std::endl;
}

void FightingActor::SaveImplementation(std::ostream& os) const{
	Actor::SaveImplementation(os);
	os << _currentHP << ' ';
	os << _baseStats.Save() << ' ';
}

void FightingActor::LoadImplementation(std::istream& is){
	pr("LOAD FIGHTINGACTOR");
	Actor::LoadImplementation(is);
	_alive = true;
	is >> _currentHP;
	prn(_currentHP);
	_baseStats = IO::ParseStruct<Stats>(is);
	_statsFromItems = CalculateStatsFromItems();
	pr("END LOAD FIGHTINGACTOR");
}

Stats FightingActor::CalculateStatsFromItems(){
	Stats itemStats;
	for(auto& item_ptr : _items){
		StatItem* statItem = dynamic_cast<StatItem*>(item_ptr.get());
		if(statItem){
			itemStats += statItem->GetStats();
		}
	}
	return itemStats;
}

}