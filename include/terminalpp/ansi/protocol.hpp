#pragma once

#include "terminalpp/core.hpp"
#include "terminalpp/detail/ascii.hpp"

//* =========================================================================
/// \namespace terminalpp::ansi
/// \brief Low-level ANSI terminal constants and operations.
//* =========================================================================
namespace terminalpp::ansi {

// Parameter Separator
static constexpr byte ps = terminalpp::detail::ascii::semi_colon;

}  // namespace terminalpp::ansi
