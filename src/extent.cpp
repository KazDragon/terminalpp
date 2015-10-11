#include "terminalpp/extent.hpp"
#include <ostream>

namespace terminalpp {

// ==========================================================================
// OSTREAM << EXTENT
// ==========================================================================
std::ostream &operator<<(std::ostream &out, extent const &ext)
{
    out << "extent(" << ext.width << ", " << ext.height << ")";
    return out;
}

}