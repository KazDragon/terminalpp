#include "string.hpp"
#include <terminalpp/string.hpp>
#include <terminalpp/terminal.hpp>
#include <ostream>

namespace terminalpp {

// ==========================================================================
// OPERATOR <<
// ==========================================================================
std::ostream &operator<<(std::ostream &out, string const &es)
{
    terminal term;
    out << term.write(es);
    return out;
}

}

