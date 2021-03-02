#include "terminalpp/control_sequence.hpp"
#include <boost/spirit/home/karma.hpp>
#include <iostream>
#include <numeric>

namespace terminalpp {

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
static void output_initiator(std::ostream &out, byte initiator, bool &comma)
{
    if (initiator != default_sequence.initiator)
    {
        output_comma(out, comma);
        out << "initiator:'" << static_cast<char>(initiator) << "'";
    }
}

// ==========================================================================
// OUTPUT_COMMAND
// ==========================================================================
static void output_command(std::ostream &out, byte command, bool &comma)
{
    if (command != default_sequence.command)
    {
        output_comma(out, comma);
        out << "command:'" << static_cast<char>(command) << "'";
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
    std::vector<byte_storage> const &arguments,
    bool &comma)
{
    if (!arguments.empty())
    {
        output_comma(out, comma);

        boost::spirit::karma::generate(
            std::ostream_iterator<char>(out),
            "args:\"" << boost::spirit::karma::string % ';' << "\"",
            arguments);
    }
}

// ==========================================================================
// OUTPUT_EXTENDER
// ==========================================================================
static void output_extender(std::ostream &out, byte extender, bool &comma)
{
    if (extender != default_sequence.extender)
    {
        output_comma(out, comma);
        out << "extender:'" << static_cast<char>(extender) << "'";
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

}
