#include "terminalpp/virtual_key.hpp"
#include <iostream>

namespace terminalpp {

// ==========================================================================
// OPERATOR==
// ==========================================================================
bool operator==(virtual_key const &lhs, virtual_key const &rhs)
{
    return lhs.key == rhs.key
        && lhs.modifiers == rhs.modifiers
        && lhs.repeat_count == rhs.repeat_count;
}

}
