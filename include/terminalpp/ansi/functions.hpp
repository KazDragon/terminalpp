#ifndef TERMINALPP_ANSI_FUNCTIONS_HPP_
#define TERMINALPP_ANSI_FUNCTIONS_HPP_

#include "terminalpp/core.hpp"
#include <string>

namespace terminalpp { namespace ansi {

// Cursor Movement and Control
std::string move_cursor_up(terminalpp::u8 amount = 1);
std::string move_cursor_down(terminalpp::u8 amount = 1);
std::string move_cursor_forward(terminalpp::u8 amount = 1);
std::string move_cursor_backward(terminalpp::u8 amount = 1);
std::string move_cursor_to_column(terminalpp::u8 amount = 1);
    
}}

#endif
