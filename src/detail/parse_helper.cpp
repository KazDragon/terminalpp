#include "terminalpp/ansi/protocol.hpp"
#include "terminalpp/detail/parse_helper.hpp"
#include <cctype>

namespace terminalpp { namespace detail {

boost::optional<terminalpp::token> parse_idle(char input, parse_temps &temps)
{
    if (input == terminalpp::ascii::ESC)
    {
        temps.state_ = state::escape;
        return {};
    }
    else
    {
        return terminalpp::token {
            terminalpp::virtual_key {
                input,
                0,
                { input }
            }
        };
    }
}

boost::optional<terminalpp::token> parse_escape(char input, parse_temps &temps)
{
    temps.initialiser_ = input;
    temps.meta_ = false;
    temps.argument_ = {};
    temps.arguments_ = {};
    temps.state_ = state::arguments;
    return {};
}

boost::optional<terminalpp::token> parse_arguments(char input, parse_temps &temps)
{
    if (isdigit(input))
    {
        temps.argument_ *= 10;
        temps.argument_ += (input - '0'); // TODO: better conversion.
    }
    else if (input  == terminalpp::ansi::PS)
    {
        temps.arguments_.push_back(temps.argument_);
        temps.argument_ = {};
    }
    else
    {
        // construct and return a control sequence.
        temps.arguments_.push_back(temps.argument_);
        temps.state_ = state::idle;

        return terminalpp::token {
            terminalpp::ansi::control_sequence {
                temps.initialiser_,
                input,
                temps.meta_,
                temps.arguments_
            }
        };
    }

    return {};
}

boost::optional<terminalpp::token> parse_helper(char input, parse_temps &temps)
{
    switch (temps.state_)
    {
        case state::idle : return parse_idle(input, temps);
        case state::escape : return parse_escape(input, temps);
        case state::arguments : return parse_arguments(input, temps);
        default :
            assert(!"state out of range");
    }

    return {};
}

}}