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

}}

#endif
