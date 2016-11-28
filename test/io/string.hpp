#pragma once

#include <iosfwd>

namespace terminalpp {

class string;

//* =========================================================================
/// \brief Streaming operator
//* =========================================================================
std::ostream &operator<<(std::ostream &out, string const &es);

}