#include "terminalpp/control_sequence.hpp"

#include <algorithm>
#include <iostream>
#include <ranges>

namespace terminalpp {

static control_sequence const default_sequence = {};

namespace {

// ==========================================================================
// OUTPUT_COMMA
// ==========================================================================
void output_comma(std::ostream &out, bool &comma)
{
    if (std::exchange(comma, true))
    {
        out << ", ";
    }
}

// ==========================================================================
// OUTPUT_INITIATOR
// ==========================================================================
void output_initiator(std::ostream &out, byte initiator, bool &comma)
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
void output_command(std::ostream &out, byte command, bool &comma)
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
void output_meta(std::ostream &out, bool meta, bool &comma)
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
void output_arguments(
    std::ostream &out, std::vector<byte_storage> const &arguments, bool &comma)
{
    if (!arguments.empty())
    {
        output_comma(out, comma);

        out << R"(args:")";

        for (auto const &value : arguments | std::views::take(1))
        {
            std::ranges::copy(value, std::ostream_iterator<char>(out));
        }

        for (auto const &value : arguments | std::views::drop(1))
        {
            out << ";";
            std::ranges::copy(value, std::ostream_iterator<char>(out));
        }

        out << R"(")";
    }
}

// ==========================================================================
// OUTPUT_EXTENDER
// ==========================================================================
void output_extender(std::ostream &out, byte extender, bool &comma)
{
    if (extender != default_sequence.extender)
    {
        output_comma(out, comma);
        out << "extender:'" << static_cast<char>(extender) << "'";
    }
}

}  // namespace

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

}  // namespace terminalpp
