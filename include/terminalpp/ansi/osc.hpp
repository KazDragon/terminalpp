#pragma once

#include "terminalpp/detail/ascii.hpp"

//* =========================================================================
/// \namespace terminalpp::ansi::osc
/// \brief Constants for commands that begin with the Operating System
/// Control sequence.
//* =========================================================================
namespace terminalpp { namespace ansi { namespace osc {

static constexpr char const SET_WINDOW_TITLE = terminalpp::detail::ascii::TWO;

}}}
