#pragma once

#include "terminalpp/string.hpp"
#include <gsl/gsl-lite.hpp>
#include <string>

namespace terminalpp {

//* =========================================================================
/// \brief A function that converts a std::string into a terminalpp::string,
/// parsing its contents according to the String To Elements protocol.
//* =========================================================================
TERMINALPP_EXPORT
terminalpp::string encode(gsl::cstring_span text);

}  // namespace terminalpp
