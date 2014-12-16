#include <iostream>

namespace Lab3{
	
class Actor : public Saveable {

public:

	Actor(std::string name) : _name(name) {}

	std::string type() const;
	std::string name() const;
	virtual void action() = 0;
	virtual void go(int direction) = 0;
	virtual void fight(const Actor& actor) = 0;
	virtual void pick_up() = 0;
	virtual void drop() = 0;
	virtual void talk_to(const Actor& actor) = 0;

protected:

	std::string _name;

	virtual void save_impl(std::ostream& os) const override;
	virtual void load_impl(std::istream& os) override;

private:

};

}