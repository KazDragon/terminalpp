#include "terminalpp/detail/terminal_charset_control.hpp"

namespace terminalpp { namespace detail {

std::string select_default_charset()
{
    return terminalpp::ansi::SELECT_DEFAULT_CHARACTER_SET;
}

std::string select_utf8_charset()
{
    return terminalpp::ansi::SELECT_UTF8_CHARACTER_SET;
}

std::string designate_g0_charset(terminalpp::ansi::charset const &cs)
{
    return terminalpp::ansi::SET_CHARSET_G0 
         + terminalpp::ansi::charset_to_string(cs);
}

std::string designate_g1_charset(terminalpp::ansi::charset const &cs)
{
    return terminalpp::ansi::SET_CHARSET_G1 
         + terminalpp::ansi::charset_to_string(cs);
}

std::string designate_g2_charset(terminalpp::ansi::charset const &cs)
{
    return terminalpp::ansi::SET_CHARSET_G2 
         + terminalpp::ansi::charset_to_string(cs);
}

std::string designate_g3_charset(terminalpp::ansi::charset const &cs)
{
    return terminalpp::ansi::SET_CHARSET_G3 
         + terminalpp::ansi::charset_to_string(cs);
}
    
}}
