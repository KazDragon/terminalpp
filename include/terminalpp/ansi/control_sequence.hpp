#ifndef TERMINALPP_ANSI_CONTROL_SEQUENCE_HPP_
#define TERMINALPP_ANSI_CONTROL_SEQUENCE_HPP_

#include <string>

namespace terminalpp { namespace ansi {

// For ANSI sequences of the format: "ESC[x;y;zC" (e.g. "ESC10;2H")
struct control_sequence
{
    char initiator;
    char command;
    bool meta;
    std::string arguments;
};

}}

#endif
