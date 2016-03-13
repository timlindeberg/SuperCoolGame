#include "FightingActor.hpp"
#include "Room.hpp"
#include "Battle.hpp"
#include "UsableItem.hpp"

namespace Lab3{

FightingActor::FightingActor() : _fled(false), _alive(true)  {}

FightingActor::~FightingActor() {}

bool FightingActor::Fight(FightingActor* actorToFight){
	if(Battle::Instance()) return false;
	Battle battle(this);
	battle.AddActor(actorToFight);

	for(auto& actor : _location->Actors()){
		FightingActor* fightingActor = dynamic_cast<FightingActor*>(actor.get());
		if(fightingActor && 
		   fightingActor != actorToFight && 
		   fightingActor != this && 
		   fightingActor->JoinBattle())
		{
			PRINT_BOX(GameStream::SUCCESS_COLOR,
				COLOR(fightingActor->Name(), BLUE) << " joined the battle!" << std::endl);
			battle.AddActor(fightingActor);
		}
	}
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
	size_t damage = Utils::NormalDistInt(stats.AP(), 0.5);

	PRINT_BOX(GameStream::SUCCESS_COLOR,
		COLOR(name, CYAN) << " attacked " << COLOR(opponent->Name(), BLUE) << " for " << 
		COLOR(damage, RED) << " damage." << std::endl);

	opponent->TakeDamage(damage, this);
}

bool FightingActor::Run(const std::string& direction){
	return Run(direction, _name);
}

bool FightingActor::Run(const std::string& direction, const std::string& name){
	if(Utils::RandomBool(0.5)){
		PRINT_BOX(GameStream::SUCCESS_COLOR,
			name << " tried to flee but failed!" << std::endl);
		return false;		
	}

	if(!Go(direction)){
		PRINT_BOX(GameStream::SUCCESS_COLOR,
			name << " tried to flee but the door was locked!" << std::endl);
		return false;		
	}

	_fled = true;
	PRINT_BOX(GameStream::SUCCESS_COLOR,
			name << " managed to flee!" << std::endl);
	return true;
}

bool FightingActor::Fled(){
	if(_fled){
		_fled = false;
		return true;
	}
	return false;
}

void FightingActor::Use(UsableItem* item){
	Use(item, _name);
}

void FightingActor::Use(UsableItem* item, const std::string& name){
	item->Use(this);
	Utils::RemoveItem(_items, item->Name());
}

Stats FightingActor::GetStats() const{
	return _baseStats + _statsFromItems;
}

int FightingActor::HP() const {
	return _currentHP;
}

double FightingActor::HPPercentage() const {
	return static_cast<double>(_currentHP) / GetStats().HP();
}

bool FightingActor::IsAlive() const {
	return _alive;
}

void FightingActor::TakeDamage(size_t damage, FightingActor* damagedBy){
	_currentHP -= damage;
	if(_currentHP <= 0){
		_alive = false;
		_currentHP = 0;
	}
}

void FightingActor::Kill() {
	Lab3::out << BeginBox(GameStream::SUCCESS_COLOR);
	Lab3::out << COLOR(_name, BLUE) << " was ";
	Lab3::out << COLOR("killed", RED) << std::endl;
	if(_items.size() > 0){
		Lab3::out << Delimiter();
		Lab3::out << COLOR(_name, BLUE) << " dropped the following item(s):" << std::endl;
		Utils::PrintListInColors(Lab3::out, _items, { Format::BLUE, Format::CYAN });
	}
	Lab3::out << EndBox();
	for(auto& item : _items){
		_location->AddItem(item);
	}
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
	Lab3::out << COLOR(Type(), BLUE) << " - " << COLOR(_name, CYAN) << std::endl;
	Stats stats = GetStats();
	double percent = HPPercentage();

	Format::Code hpColor = Utils::PercentColor(percent);
	Lab3::out << "HP: " << hpColor << (int)round(percent * 100) <<
	 	" %" << Format::FG_DEFAULT << " ( " << hpColor << _currentHP << 
	 	Format::FG_DEFAULT << " / " << COLOR(stats.HP(), GREEN) << " ) " << std::endl;
}

void FightingActor::SaveImplementation(std::ostream& os) const{
	Actor::SaveImplementation(os);
	os << _currentHP << ' ';
	os << _baseStats.Save() << ' ';
}

void FightingActor::LoadImplementation(std::istream& is){
	Actor::LoadImplementation(is);
	is >> _currentHP;
	_baseStats = IO::ParseStruct<Stats>(is);
	_statsFromItems = UpdateStatsFromItems();
}

void FightingActor::UpdateStatsFromItems() const{
	Stats itemStats;
	int HPBefore = _statsFromItems.HP();
	for(auto& item_ptr : _items){
		StatItem* statItem = dynamic_cast<StatItem*>(item_ptr.get());
		if(statItem){
			itemStats += statItem->GetStats();
		}
	}
	_statsFromItems = itemStats;
	_currentHP += (_statsFromItems.HP() - HPBefore);
	return itemStats;
}

}