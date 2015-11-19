#ifndef TERMINALPP_ANSI_SS3_HPP_
#define TERMINALPP_ANSI_SS3_HPP_

#include "terminalpp/detail/ascii.hpp"

namespace terminalpp { namespace ansi { namespace ss3 {

// Move the cursor up one character.
static constexpr char const CURSOR_UP    = terminalpp::ascii::UPPERCASE_A;
// Move the cursor down one character.
static constexpr char const CURSOR_DOWN  = terminalpp::ascii::UPPERCASE_B;
// Move the cursor right one character.
static constexpr char const CURSOR_RIGHT = terminalpp::ascii::UPPERCASE_C;
// Move the cursor left one character.
static constexpr char const CURSOR_LEFT  = terminalpp::ascii::UPPERCASE_D;
// Move the cursor to the home row.
static constexpr char const CURSOR_HOME  = terminalpp::ascii::UPPERCASE_H;
// Move to the next tab stop.
static constexpr char const CURSOR_TAB   = terminalpp::ascii::UPPERCASE_I;
// Move the cursor to the end of the line.
static constexpr char const CURSOR_END   = terminalpp::ascii::UPPERCASE_F;
// Enter key
static constexpr char const ENTER        = terminalpp::ascii::UPPERCASE_M;
// F1 Key
static constexpr char const F1           = terminalpp::ascii::UPPERCASE_P;
// F2 Key
static constexpr char const F2           = terminalpp::ascii::UPPERCASE_Q;
// F3 Key
static constexpr char const F3           = terminalpp::ascii::UPPERCASE_R;
// F4 Key
static constexpr char const F4           = terminalpp::ascii::UPPERCASE_S;
}}}

#endif
