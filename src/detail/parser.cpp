#include "terminalpp/detail/parser.hpp"
#include "terminalpp/detail/ascii.hpp"
#include "terminalpp/ansi/protocol.hpp"
#include "terminalpp/ansi/control_characters.hpp"
#include "terminalpp/ansi/csi.hpp"
#include "terminalpp/ansi/mouse.hpp"
#include <boost/range/algorithm/find_if.hpp>
#include <cctype>

namespace terminalpp { namespace detail {

namespace {

static constexpr bool is_csi_extension_character(byte input)
{
    return input == terminalpp::detail::ascii::question_mark
        || input == terminalpp::detail::ascii::greater_than
        || input == terminalpp::detail::ascii::exclamation_mark;
}

}

parser::parser()
  : state_(state::idle)
{
}

std::optional<terminalpp::token> parser::parser::operator()(byte input)
{
    switch (state_)
    {
        case state::idle      : return parse_idle(input);
        case state::cr        : return parse_cr(input);
        case state::lf        : return parse_lf(input);
        case state::escape    : return parse_escape(input);
        case state::arguments : return parse_arguments(input);
        case state::mouse0    : return parse_mouse0(input);
        case state::mouse1    : return parse_mouse1(input);
        case state::mouse2    : return parse_mouse2(input);
        default :
            assert(!"state out of range");
    }

    return {};
}

std::optional<terminalpp::token> parser::parser::parse_idle(byte input)
{
    if (input == terminalpp::detail::ascii::esc)
    {
        state_ = state::escape;
        meta_ = false;
        extender_ = '\0';
        argument_ = {};
        arguments_ = {};
        return {};
    }
    else if (input == terminalpp::detail::ascii::cr)
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
    else if (input == terminalpp::detail::ascii::lf)
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
    else if (input == terminalpp::ansi::control8::csi)
    {
        state_ = state::arguments;
        meta_ = false;
        initialiser_ = terminalpp::ansi::control7::csi[1];
        argument_ = {};
        arguments_ = {};
        return {};
    }
    else if (input == terminalpp::ansi::control8::ss3)
    {
        state_ = state::arguments;
        meta_ = false;
        initialiser_ = terminalpp::ansi::control7::ss3[1];
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

std::optional<terminalpp::token> parser::parse_cr(byte input)
{
    state_ = state::idle;

    if (input == terminalpp::detail::ascii::lf
     || input == terminalpp::detail::ascii::nul)
    {
        return {};
    }
    else
    {
        return parse_idle(input);
    }
}

std::optional<terminalpp::token> parser::parse_lf(byte input)
{
    state_ = state::idle;

    if (input == terminalpp::detail::ascii::cr)
    {
        return {};
    }
    else
    {
        return parse_idle(input);
    }
}

std::optional<terminalpp::token> parser::parse_escape(byte input)
{
    if (input == terminalpp::detail::ascii::esc)
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

std::optional<terminalpp::token> parser::parse_arguments(byte input)
{
    if (isdigit(input)) // TODO: depends on initiator.
    {
        argument_.push_back(input);
    }
    else if (input == terminalpp::ansi::ps)
    {
        arguments_.push_back(argument_);
        argument_ = {};
    }
    else if (input == terminalpp::ansi::csi::mouse_tracking
          && initialiser_ == terminalpp::ansi::control7::csi[1])
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
            terminalpp::control_sequence {
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

std::optional<terminalpp::token> parser::parse_mouse0(byte input)
{
    static constexpr struct {
        byte ansi_mouse_event;
        mouse::event_type mouse_event;
    } mouse_event_table[] = 
    {
        { ansi::mouse::left_button_down,   mouse::event_type::left_button_down   },
        { ansi::mouse::middle_button_down, mouse::event_type::middle_button_down },
        { ansi::mouse::right_button_down,  mouse::event_type::right_button_down  },
        { ansi::mouse::button_up,          mouse::event_type::button_up          },
        { ansi::mouse::no_button_change,   mouse::event_type::no_button_change   },
        { ansi::mouse::scrollwheel_up,     mouse::event_type::scrollwheel_up     },
        { ansi::mouse::scrollwheel_down,   mouse::event_type::scrollwheel_down   },
    };

    auto result = boost::find_if(
        mouse_event_table,
        [value = input - ansi::mouse::mouse_value_offset](auto const &entry)
        {
            // Note: all mouse values have an offset applied to them to make
            // the events and co-ordinates appear over the wire as printable
            // characters.
            return value == entry.ansi_mouse_event;
        });

    mouse_event_type_ = result != std::cend(mouse_event_table)
                      ? result->mouse_event
                      : mouse::event_type::no_button_change;

    state_ = state::mouse1;
    return {};
}

std::optional<terminalpp::token> parser::parse_mouse1(byte input)
{
    // In addition to the offset described above, ANSI co-ordinates are
    // 1-based, whereas Terminal++ is 0-based, which means an extra offset
    // is required.
    mouse_coordinate_.x_ = coordinate_type(
        (input - ansi::mouse::mouse_value_offset) - 1);
    state_ = state::mouse2;

    return {};
}

std::optional<terminalpp::token> parser::parse_mouse2(byte input)
{
    mouse_coordinate_.y_ = coordinate_type(
        (input - ansi::mouse::mouse_value_offset) - 1);
    state_ = state::idle;

    return {
        terminalpp::token {
            terminalpp::mouse::event {
                mouse_event_type_,
                mouse_coordinate_
            }
        }
    };
}

}}
