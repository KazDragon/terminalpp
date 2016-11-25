#pragma once

#include <terminalpp/ansi/mouse.hpp>
#include <iosfwd>

namespace terminalpp { namespace ansi { namespace mouse {

std::ostream &operator<<(
    std::ostream &out, terminalpp::ansi::mouse::report const &report);

}}}
