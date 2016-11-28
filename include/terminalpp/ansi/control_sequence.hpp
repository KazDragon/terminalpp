#pragma once

#include "terminalpp/core.hpp"
#include <string>
#include <vector>

namespace terminalpp { namespace ansi {

//* =========================================================================
/// \brief A class that encapsulates an ANSI control sequence.
/// In the sequence "ESC[x;h;yC", '[' is the initiator, "C" is the command,
/// and "x", "h" and "y" are the arguments.  Additionally, some terminals
/// send an extra escape when certain keys are held down, and if this occurs,
/// then meta is true.  Finally, some control sequences have an extender
/// character after the initiator, such as "ESC[?6n".  In this example,
/// '?' is the extender.
//* =========================================================================
struct control_sequence
{
    char initiator;
    char command;
    bool meta;
    std::vector<std::string> arguments;
    char extender = '\0';
};

//* =========================================================================
/// \brief Equality operator.
//* =========================================================================
TERMINALPP_EXPORT
bool operator==(control_sequence const &lhs, control_sequence const &rhs);

}}
