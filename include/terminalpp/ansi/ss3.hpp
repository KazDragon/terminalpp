#pragma once

#include "terminalpp/detail/ascii.hpp"

//* =========================================================================
/// \namespace terminalpp::ansi::ss3
/// \brief Constants for Single Shift to G3 commands.
///
/// \par Note
/// SS3 is not a command set per se.  Instead, it is a shift to another
/// character set for exactly one character.  However, since some of the
/// characters in that set perform actions (e.g. cursor movement), it is
/// frequently used as shortcut sequences for those commands.
//* =========================================================================
namespace terminalpp { namespace ansi { namespace ss3 {

// Move the cursor up one character.
static constexpr byte cursor_up    = terminalpp::detail::ascii::uppercase_a;
// Move the cursor down one character.
static constexpr byte cursor_down  = terminalpp::detail::ascii::uppercase_b;
// Move the cursor right one character.
static constexpr byte cursor_right = terminalpp::detail::ascii::uppercase_c;
// Move the cursor left one character.
static constexpr byte cursor_left  = terminalpp::detail::ascii::uppercase_d;
// Move the cursor to the home row.
static constexpr byte cursor_home  = terminalpp::detail::ascii::uppercase_h;
// Move to the next tab stop.
static constexpr byte cursor_tab   = terminalpp::detail::ascii::uppercase_i;
// Move the cursor to the end of the line.
static constexpr byte cursor_end   = terminalpp::detail::ascii::uppercase_f;
// Enter key
static constexpr byte enter        = terminalpp::detail::ascii::uppercase_m;
// F1 Key
static constexpr byte f1           = terminalpp::detail::ascii::uppercase_p;
// F2 Key
static constexpr byte f2           = terminalpp::detail::ascii::uppercase_q;
// F3 Key
static constexpr byte f3           = terminalpp::detail::ascii::uppercase_r;
// F4 Key
static constexpr byte f4           = terminalpp::detail::ascii::uppercase_s;

}}}
