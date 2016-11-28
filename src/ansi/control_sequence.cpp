#include "terminalpp/ansi/control_sequence.hpp"
#include <iostream>

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

}}
