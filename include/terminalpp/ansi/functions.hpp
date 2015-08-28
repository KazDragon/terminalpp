#ifndef TERMINALPP_ANSI_FUNCTIONS_HPP_
#define TERMINALPP_ANSI_FUNCTIONS_HPP_

#include "terminalpp/ansi/charset.hpp"
#include "terminalpp/core.hpp"
#include <string>

namespace terminalpp { namespace ansi {

// General Utility
std::string set_7bit_controls();
std::string set_8bit_controls();
std::string full_reset();

// DEC line modifiers
std::string double_height_line_top_half();
std::string double_height_line_bottom_half();
std::string single_width_line();
std::string double_width_line();

// Character Sets
std::string select_default_character_set();
std::string select_utf8_character_set();
std::string designate_g0_character_set(charset const &cs);
std::string designate_g1_character_set(charset const &cs);
std::string designate_g2_character_set(charset const &cs);
std::string designate_g3_character_set(charset const &cs);

// Cursor Movement and Control
std::string move_cursor_up(terminalpp::u8 amount = 1);
std::string move_cursor_down(terminalpp::u8 amount = 1);
std::string move_cursor_forward(terminalpp::u8 amount = 1);
std::string move_cursor_backward(terminalpp::u8 amount = 1);
std::string move_cursor_to_column(terminalpp::u8 amount = 1);

std::string save_cursor();
std::string restore_cursor();

}}

#endif
