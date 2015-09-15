#include "terminalpp/ansi/functions.hpp"
#include "terminalpp/ansi/protocol.hpp"
#include <cstring>

// TODO list:
//  * A lot of this can be potentially optimised after determining the
//    terminal's capabilities.
//    For example:
//    * On certain clients, instead of CSI being ESC-[, it can be a single
//      alternative character, 0x9B. Unfortunately, it prints as garbage on
//      clients that don't support this.  The same goes for other introducers
//      such as ST, OSC, PM, SS2, SS3, etc.
//
//      This feature can be enabled on certain clients by calling
//      set_8bit_controls(), but this requires on knowing that the client
//      supports it in the first place.

namespace terminalpp { namespace ansi {

// General Utility
std::string set_7bit_controls()
{
    return {
        terminalpp::ascii::ESC,
        terminalpp::ascii::SPACE,
        terminalpp::ascii::UPPERCASE_F
    };
}

std::string set_8bit_controls()
{
    return {
        terminalpp::ascii::ESC,
        terminalpp::ascii::SPACE,
        terminalpp::ascii::UPPERCASE_G
    };
}

std::string full_reset()
{
    return {
        terminalpp::ascii::ESC,
        terminalpp::ascii::LOWERCASE_C
    };
}

// DEC line modifiers
std::string double_height_line_top_half()
{
    return {
        terminalpp::ascii::ESC,
        terminalpp::ascii::HASH,
        terminalpp::ascii::THREE
    };
}

std::string double_height_line_bottom_half()
{
    return {
        terminalpp::ascii::ESC,
        terminalpp::ascii::HASH,
        terminalpp::ascii::FOUR
    };
}

std::string single_width_line()
{
    return {
        terminalpp::ascii::ESC,
        terminalpp::ascii::HASH,
        terminalpp::ascii::FIVE
    };
}

std::string double_width_line()
{
    return {
        terminalpp::ascii::ESC,
        terminalpp::ascii::HASH,
        terminalpp::ascii::SIX
    };
}

// Character Sets
std::string select_default_charset()
{
    return SELECT_DEFAULT_CHARACTER_SET;
}

std::string select_utf8_charset()
{
    return SELECT_UTF8_CHARACTER_SET;
}

std::string designate_g0_charset(charset const &cs)
{
    return SET_CHARSET_G0 + charset_to_string(cs);
}

std::string designate_g1_charset(charset const &cs)
{
    return SET_CHARSET_G1 + charset_to_string(cs);
}

std::string designate_g2_charset(charset const &cs)
{
    return SET_CHARSET_G2 + charset_to_string(cs);
}

std::string designate_g3_charset(charset const &cs)
{
    return SET_CHARSET_G3 + charset_to_string(cs);
}

std::string erase_in_display(erase_display const &how)
{
    switch (how)
    {
        default :
            // Fall-through
        case erase_display::below :
            return std::string(control7::CSI)
                 + csi::ERASE_IN_DISPLAY;

        case erase_display::above :
            return std::string(control7::CSI)
                 + csi::ERASE_IN_DISPLAY_ABOVE
                 + csi::ERASE_IN_DISPLAY;

        case erase_display::all :
            return std::string(control7::CSI)
                 + csi::ERASE_IN_DISPLAY_ALL
                 + csi::ERASE_IN_DISPLAY;
    }
}

std::string erase_in_line(erase_line const &how)
{
    switch (how)
    {
        default :
            // Fall-through
        case erase_line::right :
            return std::string(control7::CSI)
                 + csi::ERASE_IN_LINE;

        case erase_line::left :
            return std::string(control7::CSI)
                 + csi::ERASE_IN_LINE_LEFT
                 + csi::ERASE_IN_LINE;

        case erase_line::all :
            return std::string(control7::CSI)
                 + csi::ERASE_IN_LINE_ALL
                 + csi::ERASE_IN_LINE;
    }
}



}}
