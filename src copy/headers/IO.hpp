#ifndef LAB3_IO
#define LAB3_IO

#include <iostream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <vector>
#include <map>
#include <functional>
#include <memory>
#include <cxxabi.h>

#include "Utils.hpp"

#define IO_FACTORY_REGISTER_DECL(NAME) \
	static IO::FactoryRegistration<NAME> Register

#define IO_FACTORY_REGISTER_DEF(NAME) \
	IO::FactoryRegistration<NAME> NAME::Register(#NAME)

#define CREATE_INSTANCE(NAME) \
	IO::Factory<NAME>::CreateInstance(#NAME) 

namespace Lab3{

class IO {
public:

	IO();
	IO(const std::string& name);
	virtual ~IO();

	struct Factory{
	public:
		typedef std::map<std::string, std::function<IO*()> > CreationMap;	
		static IO* CreateInstance(const std::string& className);

	protected:

		static CreationMap* GetMap();
		template<class T> 
		static T* CreateInstance();

	private:
		static CreationMap* map;

	};

	template<class T>
	struct FactoryRegistration : private Factory {
		using Factory::GetMap;
		FactoryRegistration(const std::string& s);
	};

	const IO& Save() const;

	std::string Type() const;
	std::string Name() const;

	const std::string& Description() const;
	void SetName(const std::string& name);

	friend std::ostream& operator<<(std::ostream& os, const IO& saveable);
	friend std::istream& operator>>(std::istream& is, IO& saveable);

	static const char DESC_SIGN;
	static const char OBJECT_START;
	static const char OBJECT_END;
	static const char LIST_START;
	static const char LIST_END;
	static const char LIST_SEP; 
	static const char MAP_SEP;

	static std::string ReadObject(std::istream& is);
	static std::string ReadList(std::istream& is);
	static std::string ReadString(std::istream& is);

	template<class T>
	static std::unique_ptr<T> ParseObject(std::istream& is);

	template<class T> 
	static T ParseStruct(std::istream& is);

	template<class T>
	static std::vector<std::unique_ptr<T>> ParseList(std::istream& is);

	template<class T>
	static void PrintList(std::ostream& os, const std::vector<T>& list);
	static void PrintString(std::ostream& os, const std::string description);

protected:

	virtual void SaveImplementation(std::ostream& os) const = 0;
	virtual void LoadImplementation(std::istream& is) = 0;

	std::string _name;
	std::string _description;

private:

	static std::string ReadBetween(std::istream& is, char startSign, char endSign);
};


}
#include "IO.tpp"


#endif