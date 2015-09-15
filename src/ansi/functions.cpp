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

}}
