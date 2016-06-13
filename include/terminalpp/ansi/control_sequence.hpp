#pragma once

#include "terminalpp/core.hpp"
#include <string>
#include <vector>
#include <iosfwd>

namespace terminalpp { namespace ansi {

// For ANSI sequences of the format: "ESC[x;y;zC" (e.g. "ESC10;2H")
// Arguments are 'optional' in that if they had a default value, then an
// empty string value will represent that. (e.g. ESC[;H will have two empty
// string arguments.)
// Note that this must be handled by the client if the 'real' default is a
// different value (e.g. default co-ordinate positions are 1.)
// Finally, some sequences have an extra character between the initiator
// and first argument, e.g. "\x1B[?6n".  This is the extender.
struct control_sequence
{
    char initiator;
    char command;
    bool meta;
    std::vector<std::string> arguments;
    char extender = '\0';
};

TERMINALPP_EXPORT
bool operator==(control_sequence const &lhs, control_sequence const &rhs);

TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, control_sequence const &cs);

}}
