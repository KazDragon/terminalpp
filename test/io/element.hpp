#pragma once

#include <iosfwd>

namespace terminalpp {

class element;

//* =========================================================================
/// \brief Output stream operator
//* =========================================================================
std::ostream &operator<<(std::ostream &out, element const &element);

}

