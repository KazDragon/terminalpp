#include "terminalpp/ansi/control_sequence.hpp"

namespace terminalpp { namespace ansi {

bool operator==(control_sequence const &lhs, control_sequence const &rhs)
{
    return lhs.initiator == rhs.initiator
        && lhs.command == rhs.command
        && lhs.meta == rhs.meta
        && lhs.arguments.size() == rhs.arguments.size()
        && lhs.arguments == rhs.arguments;
}

}}
