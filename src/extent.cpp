#include "terminalpp/extent.hpp"
#include <ostream>
#include <string>

namespace terminalpp {

// ==========================================================================
// OPERATOR<<(STREAM,EXTENT)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, extent const &ext)
{
    return out << "extent("
               << std::to_string(ext.width)
               << ","
               << std::to_string(ext.height)
               << ")";
}

}
