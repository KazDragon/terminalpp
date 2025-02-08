#pragma once

#include "terminalpp/string.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief A function that converts a std::string into a terminalpp::string,
/// parsing its contents according to the String To Elements protocol.
//* =========================================================================
TERMINALPP_EXPORT
terminalpp::string encode(std::span<char const> text);

}  // namespace terminalpp
