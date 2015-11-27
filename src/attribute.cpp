#include "terminalpp/attribute.hpp"
#include <iostream>

namespace terminalpp {

// ==========================================================================
// STREAM OPERATOR
// ==========================================================================
std::ostream &operator<<(std::ostream &out, colour const &col)
{
    out << "colour[";
    
    // TODO: add colour type, colours.
    
    out << "]";

    return out;
}

// ==========================================================================
// STREAM OPERATOR
// ==========================================================================
std::ostream &operator<<(std::ostream &out, attribute const &attr)
{
    out << "attr[";

    // TODO: add attributes.

    out << "]";

    return out;
}

}
