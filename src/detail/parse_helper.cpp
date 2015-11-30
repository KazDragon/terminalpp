#include "terminalpp/ansi/protocol.hpp"
#include "terminalpp/detail/parse_helper.hpp"
#include <cctype>

namespace terminalpp { namespace detail {

boost::optional<terminalpp::token> parse_idle(char input, parse_temps &temps)
{
    if (input == terminalpp::ascii::ESC)
    {
        temps.state_ = state::escape;
        temps.meta_ = false;
        temps.argument_ = {};
        temps.arguments_ = {};
        return {};
    }
    else if (input == terminalpp::ascii::CR)
    {
        temps.state_ = state::cr;
        return terminalpp::token {
            terminalpp::virtual_key {
                terminalpp::vk::enter,
                terminalpp::vk_modifier::none,
                1,
                '\n'
            }
        };
    }
    else if (input == terminalpp::ascii::LF)
    {
        temps.state_ = state::lf;
        return terminalpp::token {
            terminalpp::virtual_key {
                terminalpp::vk::enter,
                terminalpp::vk_modifier::none,
                1,
                '\n'
            }
        };
    }
    else if (input == terminalpp::ansi::control8::CSI[0])
    {
        temps.state_ = state::arguments;
        temps.meta_ = false;
        temps.initialiser_ = terminalpp::ansi::control7::CSI[1];
        temps.argument_ = {};
        temps.arguments_ = {};
        return {};
    }
    else if (input == terminalpp::ansi::control8::OSC[0])
    {
        temps.state_ = state::arguments;
        temps.meta_ = false;
        temps.initialiser_ = terminalpp::ansi::control7::OSC[1];
        temps.argument_ = {};
        temps.arguments_ = {};
        return {};
    }
    else
    {
        return terminalpp::token {
            terminalpp::virtual_key {
                static_cast<vk>(input),
                terminalpp::vk_modifier::none,
                1,
                { input }
            }
        };
    }
}

boost::optional<terminalpp::token> parse_cr(char input, parse_temps &temps)
{
    temps.state_ = state::idle;

    if (input == terminalpp::ascii::LF
     || input == terminalpp::ascii::NUL)
    {
        return {};
    }
    else
    {
        return parse_idle(input, temps);
    }
}

boost::optional<terminalpp::token> parse_lf(char input, parse_temps &temps)
{
    temps.state_ = state::idle;

    if (input == terminalpp::ascii::CR)
    {
        return {};
    }
    else
    {
        return parse_idle(input, temps);
    }
}

boost::optional<terminalpp::token> parse_escape(char input, parse_temps &temps)
{
    if (input == terminalpp::ascii::ESC)
    {
        temps.meta_ = true;
    }
    else
    {
        temps.initialiser_ = input;
        temps.state_ = state::arguments;
    }
    return {};
}

boost::optional<terminalpp::token> parse_arguments(char input, parse_temps &temps)
{
    if (isdigit(input)) // TODO: depends on initiator.
    {
        temps.argument_.push_back(input);
    }
    else if (input == terminalpp::ansi::PS)
    {
        temps.arguments_.push_back(temps.argument_);
        temps.argument_ = {};
    }
    else if (input == terminalpp::ansi::csi::MOUSE_TRACKING
          && temps.initialiser_ == terminalpp::ansi::control7::CSI[1])
    {
        temps.state_ = state::mouse0;
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

boost::optional<terminalpp::token> parse_mouse0(char input, parse_temps &temps)
{
    // Mouse values have an offset applied to them to make the 
    // co-ordinates appear over the wire as printable characters.  
    temps.mouse_button_ = terminalpp::u32(
        input - ansi::mouse::MOUSE_VALUE_OFFSET);
    temps.state_ = state::mouse1;
    return {};
}

boost::optional<terminalpp::token> parse_mouse1(char input, parse_temps &temps)
{
    // In addition to the offset described above, ANSI co-ordinates are 
    // 1-based, whereas Terminal++ is 0-based, which means an extra offset
    // is required.
    temps.mouse_x_ = terminalpp::u32(
        (input - ansi::mouse::MOUSE_VALUE_OFFSET) - 1);
    temps.state_ = state::mouse2;
    return {};
}

boost::optional<terminalpp::token> parse_mouse2(char input, parse_temps &temps)
{
    temps.mouse_y_ = terminalpp::u32(
        (input - ansi::mouse::MOUSE_VALUE_OFFSET) - 1);
    temps.state_ = state::idle;

    return {
        terminalpp::token {
            terminalpp::ansi::mouse::report {
                temps.mouse_button_,
                temps.mouse_x_,
                temps.mouse_y_
            }
        }
    };
}

boost::optional<terminalpp::token> parse_helper(char input, parse_temps &temps)
{
    switch (temps.state_)
    {
        case state::idle : return parse_idle(input, temps);
        case state::cr : return parse_cr(input, temps);
        case state::lf : return parse_lf(input, temps);
        case state::escape : return parse_escape(input, temps);
        case state::arguments : return parse_arguments(input, temps);
        case state::mouse0 : return parse_mouse0(input, temps);
        case state::mouse1 : return parse_mouse1(input, temps);
        case state::mouse2 : return parse_mouse2(input, temps);
        default :
            assert(!"state out of range");
    }

    return {};
}

}}