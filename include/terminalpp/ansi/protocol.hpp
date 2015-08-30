#ifndef TERMINALPP_ANSI_PROTOCOL_HPP_
#define TERMINALPP_ANSI_PROTOCOL_HPP_

#include "terminalpp/core.hpp"
#include "terminalpp/ansi/control_characters.hpp"
#include "terminalpp/ansi/charset.hpp"
#include "terminalpp/ansi/csi.hpp"
#include "terminalpp/ansi/graphics.hpp"
#include "terminalpp/ansi/mouse.hpp"
#include "terminalpp/detail/ascii.hpp"

namespace terminalpp { namespace ansi {

// Single Character Functions and other supporting characters
static char const PS = terminalpp::ascii::SEMI_COLON; // Parameter Separator

namespace ss3 {
    // specific control codes for Single Shift Select of character set G3
    static char const HOME = terminalpp::ascii::UPPERCASE_H;
    static char const END  = terminalpp::ascii::UPPERCASE_F;
}

}}


#endif

