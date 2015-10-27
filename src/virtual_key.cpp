#include "terminalpp/virtual_key.hpp"
#include <iostream>

namespace terminalpp {

bool operator==(virtual_key const &lhs, virtual_key const &rhs)
{
    return lhs.key == rhs.key && lhs.modifiers == rhs.modifiers;
}

std::ostream &operator<<(std::ostream &out, virtual_key const &vk)
{
    return out << "vk[" << vk.key << "|" << int(vk.modifiers) << "]";
}

}