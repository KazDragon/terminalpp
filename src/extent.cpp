#include "terminalpp/extent.hpp"

#include <format>

#include <ostream>

namespace terminalpp {

// ==========================================================================
// OPERATOR<<(STREAM,EXTENT)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, extent const &ext)
{
    return out << std::format("extent({},{})", ext.width_, ext.height_);
}

}  // namespace terminalpp
