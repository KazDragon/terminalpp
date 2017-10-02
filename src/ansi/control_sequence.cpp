#include "terminalpp/ansi/control_sequence.hpp"
#include <iostream>
#include <numeric>

namespace terminalpp { namespace ansi {

// ==========================================================================
// OPERATOR==
// ==========================================================================
bool operator==(control_sequence const &lhs, control_sequence const &rhs)
{
    return lhs.initiator == rhs.initiator
        && lhs.command == rhs.command
        && lhs.meta == rhs.meta
        && lhs.arguments.size() == rhs.arguments.size()
        && lhs.arguments == rhs.arguments;
}

// ==========================================================================
// OPERATOR<<
// ==========================================================================
std::ostream &operator<<(std::ostream &out, control_sequence const &seq)
{
    static control_sequence const default_sequence = {};
    bool comma = false;

    out << "control_sequence[";

    if (seq.initiator != default_sequence.initiator)
    {
        out << "initiator:'" << seq.initiator << "'";
        comma = true;
    }

    if (seq.command != default_sequence.command)
    {
        if (comma)
        {
            out << ", ";
        }
        
        out << "command:'" << seq.command << "'";
        comma = true;
    }

    if (seq.meta)
    {
        if (comma)
        {
            out << ", ";
        }
        
        out << "meta";
        comma = true;
    }

    if (!seq.arguments.empty())
    {
        if (comma)
        {
            out << ", ";
        }
        
        out << "args:\""
            << std::accumulate(
                 seq.arguments.begin(),
                 seq.arguments.end(),
                 std::string{},
                 [](std::string &result, std::string const &current_argument)
                 {
                     if (!result.empty())
                     {
                         result += ';';
                     }

                     result += current_argument;

                     return result;
                 })
            << "\"";
        comma = true;
    }

    if (seq.extender != default_sequence.extender)
    {
        if (comma)
        {
            out << ", ";
        }
        
        out << "extender:'" << seq.extender << "'";
    }

    return out << "]";
}

}}
