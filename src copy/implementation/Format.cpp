#include "Format.hpp"

namespace Format{
	std::ostream& operator<<(std::ostream& os, Code code) {
	    return os << "\033[" << static_cast<int>(code) << "m";
	}
}
