#pragma once

#include "terminalpp/core.hpp"
#include "terminalpp/token.hpp"

namespace terminalpp::detail {

//* =========================================================================
/// \brief If the token represents a well-known virtual key (e.g. this
/// particular control sequence is shift-F12), then return a token for the
/// virtual key.  Otherwise, return the original token.
//* =========================================================================
TERMINALPP_EXPORT
[[nodiscard]] terminalpp::token get_well_known_virtual_key(
    terminalpp::token const &orig);

}  // namespace terminalpp::detail
