#pragma once

#include <iosfwd>

namespace terminalpp {

//* =========================================================================
/// \brief Stream operator for attributes.
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, attribute const &attr);

}
