#ifndef LAB3__ENVIRONMENT
#define LAB3__ENVIRONMENT

#include <vector>
#include <map>
#include <iostream>
#include <exception>

#include "IO.hpp"
#include "Actor.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include "Format.hpp"


namespace Lab3{

class Environment : public IO {

public:
	
	Environment();
	Environment(std::string name);

	const std::string& Description() const;
	std::vector<std::string> Directions() const;
	// virtual void OnPlayerEnter() = 0;
	// virtual Environment* Neighbour(Direction direction) const = 0;
	// virtual std::string Description() const = 0;
	// virtual void Enter(const Actor& actor) = 0;
	// virtual void Leave(const Actor& actor) = 0;
	// virtual void PickUp(const Entity& item) = 0;
	virtual void Drop(Entity& item);
	// virtual void Update() = 0;
	//virtual void SetExits(const std::vector<Environment> environments);
	void AddExit(const std::string& dir, Environment* e);
	void SetUpExits(const std::vector<std::unique_ptr<Environment>>& environments);
	friend std::ostream& operator<<(std::ostream& os, const Environment& env);

protected:

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& is) override;

	std::string _description;

private:

	std::map<std::string, Environment*> _exits;
	std::vector<std::unique_ptr<Actor>> _actors;
	std::vector<std::unique_ptr<Entity>> _entities;

	IO_FACTORY_REGISTER_DECL(Environment);
};

}

#endif