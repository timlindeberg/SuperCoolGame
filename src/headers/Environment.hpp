#ifndef __LAB3__ENVIRONMENT__
#define __LAB3__ENVIRONMENT__

#include <vector>
#include <map>
#include <iostream>
#include <exception>

#include "IO.hpp"
#include "Actor.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
namespace Lab3{


class Environment : public IO {

public:
	
	Environment();
	Environment(std::string name);

	std::vector<std::string> Directions() const;
	std::string Name() const;
	// virtual void OnPlayerEnter() = 0;
	// virtual Environment* Neighbour(Direction direction) const = 0;
	// virtual std::string Description() const = 0;
	// virtual void Enter(const Actor& actor) = 0;
	// virtual void Leave(const Actor& actor) = 0;
	// virtual void PickUp(const Entity& item) = 0;
	virtual void Drop(Entity& item);
	// virtual void Update() = 0;
	//virtual void SetExits(const std::vector<Environment> environments);
	void AddExit(std::string dir, Environment& e);

protected:

	virtual void SaveImplementation(std::ostream& os) const override;
	virtual void LoadImplementation(std::istream& is) override;

private:

	std::map<std::string, Environment*> _exits;
	std::vector<Entity*> _entities;
	std::string _name;



};

}

#endif