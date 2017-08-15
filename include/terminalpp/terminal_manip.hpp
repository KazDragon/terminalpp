#pragma once
#include "terminalpp/core.hpp"
#include <string>

namespace terminalpp {

class terminal;
class string;

//* =========================================================================
/// \brief Streaming operator for terminal string to terminal.
/// Results in an object that is convertible to a std::string which contains
/// the data necessary to display the terminal string on a terminal.
//* =========================================================================
TERMINALPP_EXPORT
std::string operator<<(terminal &term, string const &text);

}
