#pragma once

#include "terminalpp/detail/ascii.hpp"

//* =========================================================================
/// \namespace terminalpp::ansi::osc
/// \brief Constants for commands that begin with the Operating System
/// Control sequence.
//* =========================================================================
namespace terminalpp::ansi::osc {

static constexpr byte set_window_title = terminalpp::detail::ascii::two;

}
