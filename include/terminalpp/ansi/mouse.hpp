#pragma once

#include "terminalpp/core.hpp"
#include "terminalpp/detail/ascii.hpp"

namespace terminalpp::ansi::mouse {

// Constants for mouse actions
inline constexpr byte left_button_down = 0;
inline constexpr byte middle_button_down = 1;
inline constexpr byte right_button_down = 2;
inline constexpr byte button_up = 3;
inline constexpr byte no_button_change = 32;
inline constexpr byte scrollwheel_up = 64;
inline constexpr byte scrollwheel_down = 65;

// In standard mouse encoding, the values are transmitted by using printable
// characters starting with the space character.  This counts for both mouse
// buttons and co-ordinate values.
inline constexpr byte mouse_value_offset = terminalpp::detail::ascii::space;

}  // namespace terminalpp::ansi::mouse
