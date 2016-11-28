#pragma once

#include <iosfwd>

namespace terminalpp { namespace ansi {

class control_sequence;

//* =========================================================================
/// \brief Streaming operator.
//* =========================================================================
std::ostream &operator<<(std::ostream &out, control_sequence const &cs);

}}
