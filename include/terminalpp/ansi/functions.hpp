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
std::string select_default_charset();
std::string select_utf8_charset();
std::string designate_g0_charset(charset const &cs);
std::string designate_g1_charset(charset const &cs);
std::string designate_g2_charset(charset const &cs);
std::string designate_g3_charset(charset const &cs);

// Erase from cursor
enum class erase_display {
    below,
    above,
    all
};

std::string erase_in_display(erase_display const &how);

enum class erase_line {
    right,
    left,
    all
};

std::string erase_in_line(erase_line const &how);

}}

#endif
