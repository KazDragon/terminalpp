#include "terminalpp/element.hpp"

#include <iostream>

namespace terminalpp {

// ==========================================================================
// OPERATOR<<(STREAM, ELEMENT)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, element const &elem)
{
    out << "glyph[" << elem.glyph_ << "]";

    if (elem.attribute_ != attribute())
    {
        out << ",attribute[" << elem.attribute_ << "]";
    }

    return out;
}

}  // namespace terminalpp
