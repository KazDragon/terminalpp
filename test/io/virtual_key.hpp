#pragma once

#include <iosfwd>

namespace terminalpp {

class virtual_key;

//* =========================================================================
/// \brief Stream operator for virtual_keys.
//* =========================================================================
std::ostream &operator<<(std::ostream &out, virtual_key const &vk);

}
