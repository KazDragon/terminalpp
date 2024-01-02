#pragma once

#include "terminalpp/core.hpp"
#include "terminalpp/detail/ascii.hpp"

namespace terminalpp::ansi::mouse {

// Constants for mouse actions
static constexpr byte left_button_down = 0;
static constexpr byte middle_button_down = 1;
static constexpr byte right_button_down = 2;
static constexpr byte button_up = 3;
static constexpr byte no_button_change = 32;
static constexpr byte scrollwheel_up = 64;
static constexpr byte scrollwheel_down = 65;

// In standard mouse encoding, the values are transmitted by using printable
// characters starting with the space character.  This counts for both mouse
// buttons and co-ordinate values.
static constexpr byte mouse_value_offset = terminalpp::detail::ascii::space;

}  // namespace terminalpp::ansi::mouse
