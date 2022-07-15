#include "terminalpp/detail/well_known_virtual_key.hpp"
#include "terminalpp/ansi/control_characters.hpp"
#include "terminalpp/ansi/csi.hpp"
#include "terminalpp/ansi/dec_private_mode.hpp"
#include "terminalpp/ansi/ss3.hpp"
#include <boost/range/algorithm/find_if.hpp>
#include <utility>

using namespace terminalpp::literals;

namespace terminalpp { namespace detail {

namespace {

vk_modifier convert_modifier_argument(byte_storage const &modifier)
{
    static constexpr std::pair<byte, vk_modifier> modifier_mappings[] = {
        { ansi::csi::modifier_shift,               vk_modifier::shift },
        { ansi::csi::modifier_ctrl,                vk_modifier::ctrl  },
        { ansi::csi::modifier_alt,                 vk_modifier::alt   },
        { ansi::csi::modifier_meta,                vk_modifier::meta  },

        { ansi::csi::modifier_shift_alt,           vk_modifier::shift
                                                 | vk_modifier::alt   },
        { ansi::csi::modifier_shift_ctrl,          vk_modifier::shift
                                                 | vk_modifier::ctrl  },
        { ansi::csi::modifier_alt_ctrl,            vk_modifier::alt
                                                 | vk_modifier::ctrl  },
        { ansi::csi::modifier_shift_alt_ctrl,      vk_modifier::shift
                                                 | vk_modifier::alt
                                                 | vk_modifier::ctrl  },

        { ansi::csi::modifier_meta_shift,          vk_modifier::meta
                                                 | vk_modifier::shift },
        { ansi::csi::modifier_meta_ctrl,           vk_modifier::meta
                                                 | vk_modifier::ctrl  },
        { ansi::csi::modifier_meta_alt,            vk_modifier::meta
                                                 | vk_modifier::alt   },

        { ansi::csi::modifier_meta_shift_alt,      vk_modifier::meta
                                                 | vk_modifier::shift
                                                 | vk_modifier::alt   },
        { ansi::csi::modifier_meta_shift_ctrl,     vk_modifier::meta
                                                 | vk_modifier::shift
                                                 | vk_modifier::ctrl  },
        { ansi::csi::modifier_meta_alt_ctrl,       vk_modifier::meta
                                                 | vk_modifier::alt
                                                 | vk_modifier::ctrl  },
        { ansi::csi::modifier_meta_shift_alt_ctrl, vk_modifier::meta
                                                 | vk_modifier::shift
                                                 | vk_modifier::alt
                                                 | vk_modifier::ctrl  },
    };

    auto const value = atoi(reinterpret_cast<char const *>(modifier.c_str()));
    auto const mapping = boost::find_if(
        modifier_mappings,
        [value](auto const &inner_mapping)
        {
            return inner_mapping.first == value;
        });

    return mapping != end(modifier_mappings)
         ? mapping->second
         : vk_modifier::none;
}

token convert_control_sequence(control_sequence const &seq)
{
    // Cursor Movement commands are in the form "ESC [ C" where C is some
    // letter indicating the direction in which to move.
    static constexpr std::pair<byte, vk> const cursor_movement_commands[] = {
        { ansi::csi::cursor_up,                  vk::cursor_up    },
        { ansi::csi::cursor_down,                vk::cursor_down  },
        { ansi::csi::cursor_forward,             vk::cursor_right },
        { ansi::csi::cursor_backward,            vk::cursor_left  },
        { ansi::csi::cursor_home,                vk::home         },
        { ansi::csi::cursor_end,                 vk::end          },
        { ansi::csi::cursor_tabulation,          vk::ht           },
        { ansi::csi::cursor_backward_tabulation, vk::bt           },
    };

    assert(seq.initiator == ansi::control7::csi[1]);

    auto const &cursor_movement_command = boost::find_if(
        cursor_movement_commands,
        [&seq](auto const &elem)
        {
            return elem.first == seq.command;
        });

    if (cursor_movement_command != end(cursor_movement_commands))
    {
        auto const repeat_count_arg = seq.arguments.empty()
                                    ? byte_storage("1"_tb)
                                    : seq.arguments[0];

        auto const repeat_count = std::max(
            atoi(reinterpret_cast<char const *>(repeat_count_arg.c_str())), 
            1);

        vk_modifier const modifier =
            ( seq.arguments.size() > 1
            ? convert_modifier_argument(seq.arguments[1])
            : vk_modifier::none
            )
            | 
            ( seq.meta
            ? vk_modifier::meta
            : vk_modifier::none
            );

        return virtual_key{
            cursor_movement_command->second,
            modifier,
            repeat_count,
            seq };
    }

    return seq;
}

token convert_ss3_sequence(control_sequence const &seq)
{
    // SS3 commands are delivered as "ESC O C" where C is a letter designating
    // the command to perform.
    static constexpr std::pair<byte, vk> const ss3_commands[] = {
        { ansi::ss3::cursor_up,    vk::cursor_up    },
        { ansi::ss3::cursor_down,  vk::cursor_down  },
        { ansi::ss3::cursor_right, vk::cursor_right },
        { ansi::ss3::cursor_left,  vk::cursor_left  },
        { ansi::ss3::cursor_home,  vk::home         },
        { ansi::ss3::cursor_end,   vk::end          },
        { ansi::ss3::cursor_tab,   vk::ht           },
        { ansi::ss3::enter,        vk::enter        },
        { ansi::ss3::f1,           vk::f1           },
        { ansi::ss3::f2,           vk::f2           },
        { ansi::ss3::f3,           vk::f3           },
        { ansi::ss3::f4,           vk::f4           },
    };

    assert(seq.initiator == ansi::control7::ss3[1]);

    auto const &ss3_command = boost::find_if(
        ss3_commands,
        [&seq](auto const &elem)
        {
            return elem.first == seq.command;
        });

    if (ss3_command != end(ss3_commands))
    {
        vk_modifier const modifier = seq.meta
                                   ? vk_modifier::meta
                                   : vk_modifier::none;

        return virtual_key{
            ss3_command->second,
            modifier,
            1,
            seq };
    }

    return seq;
}

token convert_keypad_sequence(control_sequence const &seq)
{
    // Keypad commands are delivered as "ESC [ N ~" where N is a number
    // designating the key pressed.
    static constexpr std::pair<char, vk> const keypad_commands[] = {
        { ansi::csi::keypad_home,   vk::home },
        { ansi::csi::keypad_insert, vk::ins  },
        { ansi::csi::keypad_del,    vk::del  },
        { ansi::csi::keypad_end,    vk::end  },
        { ansi::csi::keypad_pgup,   vk::pgup },
        { ansi::csi::keypad_pgdn,   vk::pgdn },
        { ansi::csi::keypad_f1,     vk::f1   },
        { ansi::csi::keypad_f2,     vk::f2   },
        { ansi::csi::keypad_f3,     vk::f3   },
        { ansi::csi::keypad_f4,     vk::f4   },
        { ansi::csi::keypad_f5,     vk::f5   },
        { ansi::csi::keypad_f6,     vk::f6   },
        { ansi::csi::keypad_f7,     vk::f7   },
        { ansi::csi::keypad_f8,     vk::f8   },
        { ansi::csi::keypad_f9,     vk::f9   },
        { ansi::csi::keypad_f10,    vk::f10  },
        { ansi::csi::keypad_f11,    vk::f11  },
        { ansi::csi::keypad_f12,    vk::f12  },
    };

    assert(seq.command == ansi::csi::keypad_function);

    if (seq.arguments[0].empty() || !isdigit(seq.arguments[0][0]))
    {
        // Nothing will match.
        return seq;
    }

    auto const argument = atoi(
        reinterpret_cast<char const *>(seq.arguments[0].c_str()));

    auto const &keypad_command = boost::find_if(
        keypad_commands,
        [argument](auto const &elem)
        {
            return argument == elem.first;
        });

    if (keypad_command != end(keypad_commands))
    {
        vk_modifier const modifier =
            ( seq.arguments.size() > 1
              ? convert_modifier_argument(seq.arguments[1])
              : vk_modifier::none
            )
            | 
            ( seq.meta
            ? vk_modifier::meta
            : vk_modifier::none
            );

        return virtual_key{
            keypad_command->second,
            modifier,
            1,
            seq };
    }

    return seq;
}

token convert_common_control_sequence(control_sequence const &seq)
{
    if (seq.initiator == ansi::control7::csi[1])
    {
        if (seq.command == ansi::csi::keypad_function)
        {
            return convert_keypad_sequence(seq);
        }

        return convert_control_sequence(seq);
    }
    else if (seq.initiator == ansi::control7::ss3[1])
    {
        return convert_ss3_sequence(seq);
    }

    return seq;
}

template <typename... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <typename... Ts> overloaded(Ts...) -> overloaded<Ts...>;

}

// ==========================================================================
// GET_WELL_KNOWN_VIRTUAL_KEY
// ==========================================================================
token get_well_known_virtual_key(token const &tok)
{
    return std::visit(overloaded{
        [](control_sequence const &seq)
        {
            return convert_common_control_sequence(seq);
        },
        [](auto &&t) -> token
        {
            return t;
        }},
        tok);
}

}}
