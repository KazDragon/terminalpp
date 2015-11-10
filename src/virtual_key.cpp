#include "terminalpp/virtual_key.hpp"
#include <iostream>

namespace terminalpp {

bool operator==(virtual_key const &lhs, virtual_key const &rhs)
{
    return lhs.key == rhs.key
        && lhs.modifiers == rhs.modifiers
        && lhs.repeat_count == rhs.repeat_count;
}

std::ostream &operator<<(std::ostream &out, virtual_key const &vk)
{
    return out << "vk[" << static_cast<int>(vk.key)
        << "|" << int(vk.modifiers) << "("
        << int(vk.repeat_count) << ")]";
}

}