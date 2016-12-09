#include "terminalpp/detail/parser.hpp"
#include "terminalpp/ansi/protocol.hpp"
#include <cctype>

namespace terminalpp { namespace detail {

namespace {

bool is_csi_extension_character(char input)
{
    return input == terminalpp::detail::ascii::QUESTION_MARK
        || input == terminalpp::detail::ascii::GREATER_THAN
        || input == terminalpp::detail::ascii::EXCLAMATION_MARK;
}

}

parser::parser()
  : state_(state::idle)
{
}

boost::optional<terminalpp::token> parser::parser::operator()(char input)
{
    switch (state_)
    {
        case state::idle : return parse_idle(input);
        case state::cr : return parse_cr(input);
        case state::lf : return parse_lf(input);
        case state::escape : return parse_escape(input);
        case state::arguments : return parse_arguments(input);
        case state::mouse0 : return parse_mouse0(input);
        case state::mouse1 : return parse_mouse1(input);
        case state::mouse2 : return parse_mouse2(input);
        default :
            assert(!"state out of range");
    }

    return {};
}

boost::optional<terminalpp::token> parser::parser::parse_idle(char input)
{
    if (input == terminalpp::detail::ascii::ESC)
    {
        state_ = state::escape;
        meta_ = false;
        extender_ = '\0';
        argument_ = {};
        arguments_ = {};
        return {};
    }
    else if (input == terminalpp::detail::ascii::CR)
    {
        state_ = state::cr;
        return terminalpp::token {
            terminalpp::virtual_key {
                terminalpp::vk::enter,
                terminalpp::vk_modifier::none,
                1,
                '\n'
            }
        };
    }
    else if (input == terminalpp::detail::ascii::LF)
    {
        state_ = state::lf;
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
        state_ = state::arguments;
        meta_ = false;
        initialiser_ = terminalpp::ansi::control7::CSI[1];
        argument_ = {};
        arguments_ = {};
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

boost::optional<terminalpp::token> parser::parse_cr(char input)
{
    state_ = state::idle;

    if (input == terminalpp::detail::ascii::LF
     || input == terminalpp::detail::ascii::NUL)
    {
        return {};
    }
    else
    {
        return parse_idle(input);
    }
}

boost::optional<terminalpp::token> parser::parse_lf(char input)
{
    state_ = state::idle;

    if (input == terminalpp::detail::ascii::CR)
    {
        return {};
    }
    else
    {
        return parse_idle(input);
    }
}

boost::optional<terminalpp::token> parser::parse_escape(char input)
{
    if (input == terminalpp::detail::ascii::ESC)
    {
        meta_ = true;
    }
    else
    {
        initialiser_ = input;
        state_ = state::arguments;
    }
    return {};
}

boost::optional<terminalpp::token> parser::parse_arguments(char input)
{
    if (isdigit(input)) // TODO: depends on initiator.
    {
        argument_.push_back(input);
    }
    else if (input == terminalpp::ansi::PS)
    {
        arguments_.push_back(argument_);
        argument_ = {};
    }
    else if (input == terminalpp::ansi::csi::MOUSE_TRACKING
          && initialiser_ == terminalpp::ansi::control7::CSI[1])
    {
        state_ = state::mouse0;
    }
    else if (is_csi_extension_character(input))
    {
        extender_ = input;
    }
    else
    {
        // construct and return a control sequence.
        arguments_.push_back(argument_);
        state_ = state::idle;

        return terminalpp::token {
            terminalpp::ansi::control_sequence {
                initialiser_,
                input,
                meta_,
                arguments_,
                extender_
            }
        };
    }

    return {};
}

boost::optional<terminalpp::token> parser::parse_mouse0(char input)
{
    // Mouse values have an offset applied to them to make the
    // co-ordinates appear over the wire as printable characters.
    mouse_button_ = terminalpp::u32(
        input - ansi::mouse::MOUSE_VALUE_OFFSET);
    state_ = state::mouse1;
    return {};
}

boost::optional<terminalpp::token> parser::parse_mouse1(char input)
{
    // In addition to the offset described above, ANSI co-ordinates are
    // 1-based, whereas Terminal++ is 0-based, which means an extra offset
    // is required.
    mouse_x_ = terminalpp::u32(
        (input - ansi::mouse::MOUSE_VALUE_OFFSET) - 1);
    state_ = state::mouse2;
    return {};
}

boost::optional<terminalpp::token> parser::parse_mouse2(char input)
{
    mouse_y_ = terminalpp::u32(
        (input - ansi::mouse::MOUSE_VALUE_OFFSET) - 1);
    state_ = state::idle;

    return {
        terminalpp::token {
            terminalpp::ansi::mouse::report {
                mouse_button_,
                mouse_x_,
                mouse_y_
            }
        }
    };
}

}}