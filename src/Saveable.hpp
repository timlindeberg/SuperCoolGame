#include <iostream>

namespace Lab3{

class Saveable{

public:

	const Saveable& save() const;

	friend std::ostream& operator<<(std::ostream& os, const Saveable& saveable);
	friend std::istream& operator>>(std::istream& is, Saveable& saveable);

protected:

	virtual void save_impl(std::ostream& os) const = 0;
	virtual void load_impl(std::istream& is) = 0;

};

}