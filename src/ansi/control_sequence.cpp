#include "terminalpp/ansi/control_sequence.hpp"
#include <iostream>
#include <numeric>

namespace terminalpp { namespace ansi {

static control_sequence const default_sequence = {};

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
// OUTPUT_COMMA
// ==========================================================================
static void output_comma(std::ostream &out, bool &comma)
{
    if (comma)
    {
        out << ", ";
    }

    comma = true;
}

// ==========================================================================
// OUTPUT_INITIATOR
// ==========================================================================
static void output_initiator(std::ostream &out, char initiator, bool &comma)
{
    if (initiator != default_sequence.initiator)
    {
        output_comma(out, comma);
        out << "initiator:'" << initiator << "'";
    }
}

// ==========================================================================
// OUTPUT_COMMAND
// ==========================================================================
static void output_command(std::ostream &out, char command, bool &comma)
{
    if (command != default_sequence.command)
    {
        output_comma(out, comma);
        out << "command:'" << command << "'";
    }
}

// ==========================================================================
// OUTPUT_META
// ==========================================================================
static void output_meta(std::ostream &out, bool meta, bool &comma)
{
    if (meta != default_sequence.meta)
    {
        output_comma(out, comma);
        out << "meta";
    }
}

// ==========================================================================
// OUTPUT_ARGUMENTS
// ==========================================================================
static void output_arguments(
    std::ostream &out,
    std::vector<std::string> const &arguments,
    bool &comma)
{
    if (!arguments.empty())
    {
        output_comma(out, comma);

        out << "args:\""
            << std::accumulate(
                 arguments.begin(),
                 arguments.end(),
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
    }
}

// ==========================================================================
// OUTPUT_EXTENDER
// ==========================================================================
static void output_extender(std::ostream &out, char extender, bool &comma)
{
    if (extender != default_sequence.extender)
    {
        output_comma(out, comma);
        out << "extender:'" << extender << "'";
    }
}

// ==========================================================================
// OPERATOR<<
// ==========================================================================
std::ostream &operator<<(std::ostream &out, control_sequence const &seq)
{
    bool comma = false;

    out << "control_sequence[";
    output_initiator(out, seq.initiator, comma);
    output_command(out, seq.command, comma);
    output_meta(out, seq.meta, comma);
    output_arguments(out, seq.arguments, comma);
    output_extender(out, seq.extender, comma);
    return out << "]";
}

}}
