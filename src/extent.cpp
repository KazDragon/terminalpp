#include "terminalpp/extent.hpp"
#include <fmt/format.h>
#include <ostream>
#include <string>

namespace terminalpp {

// ==========================================================================
// OPERATOR<<(STREAM,EXTENT)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, extent const &ext)
{
  return out << fmt::format("extent({},{})", ext.width_, ext.height_);
}

}  // namespace terminalpp
