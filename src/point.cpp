#include "terminalpp/point.hpp"
#include <ostream>
#include <string>

namespace terminalpp {

// ==========================================================================
// OPERATOR<<(STREAM,POINT)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, point const &pt)
{
    return out << "point("
               << std::to_string(pt.x_)
               << ","
               << std::to_string(pt.y_)
               << ")";
}

}
