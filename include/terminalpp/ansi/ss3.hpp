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
namespace terminalpp::ansi::ss3 {

// clang-format off
// Move the cursor up one character.
inline constexpr byte cursor_up    = terminalpp::detail::ascii::uppercase_a;
// Move the cursor down one character.
inline constexpr byte cursor_down  = terminalpp::detail::ascii::uppercase_b;
// Move the cursor right one character.
inline constexpr byte cursor_right = terminalpp::detail::ascii::uppercase_c;
// Move the cursor left one character.
inline constexpr byte cursor_left  = terminalpp::detail::ascii::uppercase_d;
// Move the cursor to the home row.
inline constexpr byte cursor_home  = terminalpp::detail::ascii::uppercase_h;
// Move to the next tab stop.
inline constexpr byte cursor_tab   = terminalpp::detail::ascii::uppercase_i;
// Move the cursor to the end of the line.
inline constexpr byte cursor_end   = terminalpp::detail::ascii::uppercase_f;
// Enter key
inline constexpr byte enter        = terminalpp::detail::ascii::uppercase_m;
// F1 Key
inline constexpr byte f1           = terminalpp::detail::ascii::uppercase_p;
// F2 Key
inline constexpr byte f2           = terminalpp::detail::ascii::uppercase_q;
// F3 Key
inline constexpr byte f3           = terminalpp::detail::ascii::uppercase_r;
// F4 Key
inline constexpr byte f4           = terminalpp::detail::ascii::uppercase_s;
// clang-format on

}  // namespace terminalpp::ansi::ss3
