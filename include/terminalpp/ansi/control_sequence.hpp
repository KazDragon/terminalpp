#ifndef TERMINALPP_ANSI_CONTROL_SEQUENCE_HPP_
#define TERMINALPP_ANSI_CONTROL_SEQUENCE_HPP_

#include "terminalpp/core.hpp"
#include <string>
#include <vector>
#include <iosfwd>

namespace terminalpp { namespace ansi {

// For ANSI sequences of the format: "ESC[x;y;zC" (e.g. "ESC10;2H")
// Arguments are 'optional' in that if they had a default value, then a
// value of 0 will represent that. (e.g. ESC[;H will have two 0 arguments).
// Note that this must be handled by the client if the 'real' default is a
// different value (e.g. default co-ordinate positions are 1.)
struct control_sequence
{
    char initiator;
    char command;
    bool meta;
    std::vector<terminalpp::u32> arguments;
};

bool operator==(control_sequence const &lhs, control_sequence const &rhs);

std::ostream &operator<<(std::ostream &out, control_sequence const &cs);

}}

#endif
