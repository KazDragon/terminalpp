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

namespace terminalpp { namespace ansi {

namespace {

std::string move_cursor(terminalpp::u8 amount, char direction)
{
    if (amount == 1)
    {
        return std::string(control7::CSI)
             + direction;
    }
    else
    {
        static char const format_str[] = "%s%d%c";
        char str[7];
        sprintf(
            str,
            format_str,
            control7::CSI,
            u32(amount),
            direction);
        return str;
    }
}

}

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
std::string select_default_character_set()
{
    return SELECT_DEFAULT_CHARACTER_SET;
}

std::string select_utf8_character_set()
{
    return SELECT_UTF8_CHARACTER_SET;
}

std::string designate_g0_character_set(charset const &cs)
{
    return SET_CHARSET_G0 + charset_to_string(cs);
}

std::string designate_g1_character_set(charset const &cs)
{
    return SET_CHARSET_G1 + charset_to_string(cs);
}

std::string designate_g2_character_set(charset const &cs)
{
    return SET_CHARSET_G2 + charset_to_string(cs);
}

std::string designate_g3_character_set(charset const &cs)
{
    return SET_CHARSET_G3 + charset_to_string(cs);
}

// Cursor Movement and Control
std::string move_cursor_up(terminalpp::u8 amount)
{
    return move_cursor(amount, csi::CURSOR_UP);
}

std::string move_cursor_down(terminalpp::u8 amount)
{
    return move_cursor(amount, csi::CURSOR_DOWN);
}

std::string move_cursor_forward(terminalpp::u8 amount)
{
    return move_cursor(amount, csi::CURSOR_FORWARD);
}

std::string move_cursor_backward(terminalpp::u8 amount)
{
    return move_cursor(amount, csi::CURSOR_BACKWARD);
}

std::string move_cursor_to_column(terminalpp::u8 amount)
{
    return move_cursor(amount, csi::CURSOR_HORIZONTAL_ABSOLUTE);
}

std::string save_cursor()
{
    // TODO: Depending on the terminal's capabilities, this might
    // need to be CSI s instead.
    return {
        terminalpp::ascii::ESC,
        terminalpp::ascii::SEVEN
    };
}

std::string restore_cursor()
{
    // TODO: Depending on the terminal's capabilities, this might
    // need to be CSI u instead.
    return {
        terminalpp::ascii::ESC,
        terminalpp::ascii::EIGHT
    };
}



}}
