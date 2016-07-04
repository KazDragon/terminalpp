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
static constexpr char const CURSOR_UP    = terminalpp::detail::ascii::UPPERCASE_A;
// Move the cursor down one character.
static constexpr char const CURSOR_DOWN  = terminalpp::detail::ascii::UPPERCASE_B;
// Move the cursor right one character.
static constexpr char const CURSOR_RIGHT = terminalpp::detail::ascii::UPPERCASE_C;
// Move the cursor left one character.
static constexpr char const CURSOR_LEFT  = terminalpp::detail::ascii::UPPERCASE_D;
// Move the cursor to the home row.
static constexpr char const CURSOR_HOME  = terminalpp::detail::ascii::UPPERCASE_H;
// Move to the next tab stop.
static constexpr char const CURSOR_TAB   = terminalpp::detail::ascii::UPPERCASE_I;
// Move the cursor to the end of the line.
static constexpr char const CURSOR_END   = terminalpp::detail::ascii::UPPERCASE_F;
// Enter key
static constexpr char const ENTER        = terminalpp::detail::ascii::UPPERCASE_M;
// F1 Key
static constexpr char const F1           = terminalpp::detail::ascii::UPPERCASE_P;
// F2 Key
static constexpr char const F2           = terminalpp::detail::ascii::UPPERCASE_Q;
// F3 Key
static constexpr char const F3           = terminalpp::detail::ascii::UPPERCASE_R;
// F4 Key
static constexpr char const F4           = terminalpp::detail::ascii::UPPERCASE_S;

}}}
