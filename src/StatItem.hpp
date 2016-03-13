#ifndef LAB3__STAT_ITEM
#define LAB3__STAT_ITEM

#include "Item.hpp"
#include "Stats.hpp"

namespace Lab3{

class StatItem : public Item {
public:

	StatItem();
	Item* Clone() const;

	Stats GetStats();

	friend std::ostream& operator<<(std::ostream& os, const StatItem& e);

protected:

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& os) override;

	Stats _stats;

private:

	IO_FACTORY_REGISTER_DECL(StatItem);

};

}

#endif