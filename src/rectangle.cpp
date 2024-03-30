#include "terminalpp/rectangle.hpp"

#include <ostream>

namespace terminalpp {

// ==========================================================================
// OPERATOR<<(OSTREAM, RECTANGLE)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, terminalpp::rectangle const &rect)
{
    return out << "rectangle(" << rect.origin_ << ", " << rect.size_ << ")";
}

}  // namespace terminalpp
