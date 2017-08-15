#include "terminalpp/terminal_manip.hpp"
#include "terminalpp/terminal.hpp"

namespace terminalpp {

std::string operator<<(terminal &term, string const &text)
{
    return term.write(text);
}

}