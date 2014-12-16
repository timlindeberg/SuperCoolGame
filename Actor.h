namespace Lab3{
	
class Actor {

public:

	Actor(std::string name) : _name(name);

	std::string type();
	std::string name();
	void action();
	void go(int direction);
	void fight(const Actor& actor);
	void pick_up();
	void drop();
	void talk_to(const Actor& actor);

protected:

	std::string _name;

}

}