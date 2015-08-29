#ifndef TERMINALPP_ANSI_PROTOCOL_HPP_
#define TERMINALPP_ANSI_PROTOCOL_HPP_

#include "terminalpp/core.hpp"
#include "terminalpp/ascii/protocol.hpp"
#include "terminalpp/ansi/control_characters.hpp"
#include "terminalpp/ansi/charset.hpp"
#include "terminalpp/ansi/csi.hpp"
#include "terminalpp/ansi/graphics.hpp"
#include "terminalpp/ansi/mouse.hpp"

#include <string>

namespace terminalpp { namespace ansi {

// Single Character Functions and other supporting characters
static char const PS = terminalpp::ascii::SEMI_COLON; // Parameter Separator

namespace ss3 {
    // specific control codes for Single Shift Select of character set G3
    static char const HOME                         = terminalpp::ascii::UPPERCASE_H;
    static char const END                          = terminalpp::ascii::UPPERCASE_F;
}

// For ANSI sequences of the format: ESC[x;y;zC (e.g. "ESC[10;2H"
// In the above example, "[" is the initiator, "H" is the command, and
// "10;2" is the arguments.
struct control_sequence
{
    std::string arguments_;
    bool        meta_;
    char        initiator_;
    char        command_;
};

constexpr inline bool operator==(control_sequence const& lhs, control_sequence const& rhs)
{
    return lhs.meta_      == rhs.meta_
        && lhs.command_   == rhs.command_
        && lhs.initiator_ == rhs.initiator_
        && lhs.arguments_ == rhs.arguments_;
}

}}


#endif

