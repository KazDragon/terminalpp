#include "terminalpp/point.hpp"
#include <ostream>

namespace terminalpp {

// ==========================================================================
// OPERATOR<<(STREAM,POINT)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, point const &pt)
{
    return out << "point("
               << std::to_string(pt.x)
               << ","
               << std::to_string(pt.y)
               << ")";
}

}
