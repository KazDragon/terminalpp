#include "terminalpp/rectangle.hpp"
#include <ostream>

namespace terminalpp {

// ==========================================================================
// OSTREAM << RECTANGLE
// ==========================================================================
std::ostream &operator<<(std::ostream &out, rectangle const &rect)
{
    out << "rectangle[" << rect.origin << ", " << rect.size << "]";
    return out;
}

}
