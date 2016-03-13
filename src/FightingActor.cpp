#include "FightingActor.hpp"
#include "Room.hpp"
#include "Battle.hpp"
#include "UsableItem.hpp"

namespace Lab3{

FightingActor::FightingActor() : _fled(false), _alive(true)  {}

FightingActor::~FightingActor() {}

bool FightingActor::Fight(FightingActor* actorToFight){
	if(Battle::Instance()) return false;
	Battle* battle = new Battle(this);
	battle->AddActor(actorToFight);

	for(auto& actor : _location->Actors()){
		FightingActor* fightingActor = dynamic_cast<FightingActor*>(actor.get());
		if(fightingActor && 
		   fightingActor != actorToFight && 
		   fightingActor != this && 
		   fightingActor->JoinBattle())
		{
			PRINT_BOX(GameStream::SUCCESS_COLOR,
				COLOR(fightingActor->Name(), BLUE) << " joined the battle!" << std::endl);
			battle->AddActor(fightingActor);
		}
	}
	return true;
}

void FightingActor::Attack(FightingActor* opponent){
	Attack(opponent, _name);
}

void FightingActor::Attack(FightingActor* opponent, const std::string& name){
	if(Utils::RandomBool(0.2)){
		PRINT_BOX(GameStream::SUCCESS_COLOR,
			name << " missed!" << std::endl);
		return;
	}

	Stats stats = GetStats();
	size_t damage = Utils::NormalDistInt(stats.AP(), 1.0);

	PRINT_BOX(GameStream::SUCCESS_COLOR,
		COLOR(name, CYAN) << " attacked " << COLOR(opponent->Name(), BLUE) << " for " << 
		COLOR(damage, RED) << " damage." << std::endl);

	opponent->TakeDamage(damage);
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

void FightingActor::Take(const std::string& itemName){
	Actor::Take(itemName);
	UpdateStatsFromItems();
}

void FightingActor::Drop(const std::string& itemName){
	Actor::Drop(itemName);
	UpdateStatsFromItems();
}

Stats FightingActor::GetStats() const{
	return _baseStats + _statsFromItems;
}

void FightingActor::SetStats(const Stats& stats){
	_baseStats = stats;
}

int FightingActor::HP() const {
	return _currentHP;
}

void FightingActor::SetHP(size_t hp){
	_currentHP = hp;
}

double FightingActor::HPPercentage() const {
	return static_cast<double>(_currentHP) / GetStats().HP();
}

bool FightingActor::IsAlive() const {
	return _alive;
}

void FightingActor::TakeDamage(size_t damage){
	_currentHP -= damage;
	if(_currentHP <= 0){
		_alive = false;
		_currentHP = 0;
	}
}

void FightingActor::TakeHeal(size_t heal){
	int max = GetStats().HP();
	_currentHP += heal;
	if(_currentHP >= max)
		_currentHP = max;
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

void FightingActor::PrintBattleDescription(){
	Lab3::out << COLOR(Type(), BLUE) << " - " << COLOR(_name, CYAN) << std::endl;
	Stats stats = GetStats();
	double percent = HPPercentage();

	Format::Code hpColor = Utils::PercentColor(percent);
	Lab3::out << "    " <<  "HP: " << hpColor << (int)round(percent * 100) <<
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
	UpdateStatsFromItems();
}

void FightingActor::UpdateStatsFromItems(){
	Stats itemStats;
	int HPBefore = _statsFromItems.HP();
	for(auto& item_ptr : _items){
		StatItem* statItem = dynamic_cast<StatItem*>(item_ptr.get());
		if(statItem){
			itemStats += statItem->GetStats();
		}
	}
	_statsFromItems = itemStats;
	_currentHP += (itemStats.HP() - HPBefore);
}

}