#include "terminalpp/string.hpp"

#include "terminalpp/element.hpp"

#include <cstring>

namespace terminalpp {

// ==========================================================================
// OPERATOR <<
// ==========================================================================
std::ostream &operator<<(std::ostream &out, string const &text)
{
    bool add_comma = false;

    for (auto const &elem : text)
    {
        if (add_comma)
        {
            out << ",";
        }

        out << "element[" << elem << "]";

        add_comma = true;
    }

    return out;
}

}  // namespace terminalpp
