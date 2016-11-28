#include "virtual_key.hpp"
#include <terminalpp/virtual_key.hpp>

namespace terminalpp {

// ==========================================================================
// OPERATOR<<
// ==========================================================================
std::ostream &operator<<(std::ostream &out, virtual_key const &vk)
{
    return out << "vk[" << static_cast<int>(vk.key)
        << "|" << int(vk.modifiers) << "("
        << int(vk.repeat_count) << ")]";
}

}
