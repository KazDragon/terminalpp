#include "string.hpp"
#include <terminalpp/string.hpp>
#include <terminalpp/default_terminal.hpp>
#include <ostream>

namespace terminalpp {

// ==========================================================================
// OPERATOR <<
// ==========================================================================
std::ostream &operator<<(std::ostream &out, string const &es)
{
    default_terminal term;
    out << term.write(es);
    return out;
}

}

