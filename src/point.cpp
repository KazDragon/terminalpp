#include "terminalpp/point.hpp"
#include <ostream>

namespace terminalpp {

// ==========================================================================
// OSTREAM << POINT
// ==========================================================================
std::ostream &operator<<(std::ostream &out, point const &pt)
{
    out << "point(" << pt.x << ", " << pt.y << ")";
    return out;
}

}
