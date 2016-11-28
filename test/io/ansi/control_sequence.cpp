#include "control_sequence.hpp"
#include <terminalpp/ansi/control_sequence.hpp>
#include <iostream>

namespace terminalpp { namespace ansi {

std::ostream &operator<<(std::ostream &out, control_sequence const &cs)
{
    out << "control_sequence["
        << "initiator=" << cs.initiator
        << ",command=" << cs.command
        << ",meta=" << cs.meta
        << ",arguments=[";

    for (auto const &argument : cs.arguments)
    {
        out << argument << ",";
    }

    return out << "]]";
}

}}
