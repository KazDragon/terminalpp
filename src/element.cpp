#include "terminalpp/element.hpp"
#include <iostream>

namespace terminalpp {

// ==========================================================================
// STREAM OPERATOR
// ==========================================================================
std::ostream &operator<<(std::ostream &out, element const &attr)
{
    out << "elem[" << attr.glyph_ << ", " << attr.attribute_ << "]";
    return out;
}

}
