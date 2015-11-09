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
// Move the cursor to the end of the line.
static constexpr char const CURSOR_END   = terminalpp::ascii::UPPERCASE_F;

}}}

#endif
