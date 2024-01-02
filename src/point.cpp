#include "terminalpp/point.hpp"
#include <fmt/format.h>
#include <ostream>
#include <string>

namespace terminalpp {

// ==========================================================================
// OPERATOR<<(STREAM,POINT)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, point const &pt)
{
  return out << fmt::format("point({},{})", pt.x_, pt.y_);
}

}  // namespace terminalpp
