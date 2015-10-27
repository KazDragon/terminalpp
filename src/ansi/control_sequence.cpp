#include "terminalpp/ansi/control_sequence.hpp"
#include <algorithm>

namespace terminalpp { namespace ansi {

bool operator==(control_sequence const &lhs, control_sequence const &rhs)
{
    if (lhs.initiator == rhs.initiator
        && lhs.command == rhs.command
        && lhs.meta == rhs.meta)
    {
        // TODO: look up an algorithm to do this.  Mismatch? Equal_Range
        if (lhs.arguments.size() != rhs.arguments.size())
        {
            return false;
        }

        for (auto itl = lhs.arguments.begin(), itr = rhs.arguments.begin();
             itl != lhs.arguments.end();
             ++itl, ++itr)
        {
            if (*itl != *itr)
            {
                return false;
            }
        }

        return true;
    }

    return false;
}

std::ostream &operator<<(std::ostream &out, control_sequence const &cs)
{
    out << "control_sequence["
        << "initiator=" << cs.initiator
        << ",command=" << cs.command
        << ",meta=" << cs.meta
        << ",arguments=[";

    for (auto argument : cs.arguments)
    {
        out << argument << ",";
    }

    return out << "]]";
}

}}
