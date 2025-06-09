#include "terminalpp/point.hpp"

#include <format>

#include <ostream>

namespace terminalpp {

// ==========================================================================
// OPERATOR<<(STREAM,POINT)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, point const &pt)
{
    return out << std::format("point({},{})", pt.x_, pt.y_);
}

}  // namespace terminalpp
