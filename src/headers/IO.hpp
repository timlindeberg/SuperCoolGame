#ifndef __LAB3__SAVEABLE__
#define __LAB3__SAVEABLE__

#include <iostream>
#include <sstream>
#include <exception>
#include <vector>

namespace Lab3{

class IO{

public:

	const IO& Save() const;

	friend std::ostream& operator<<(std::ostream& os, const IO& saveable);
	friend std::istream& operator>>(std::istream& is, IO& saveable);

	static const char OBJECT_SEP;
	static const char LIST_SEP; 
	static const char MAP_SEP;
	static std::string ReadObject(std::istream& is);
	static std::vector<std::string> ReadList(std::istream& is);

protected:

	virtual void SaveImplementation(std::ostream& os) const = 0;
	virtual void LoadImplementation(std::istream& is) = 0;
};

}

#endif