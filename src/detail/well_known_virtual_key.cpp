#include "terminalpp/detail/well_known_virtual_key.hpp"
#include "terminalpp/ansi/control_characters.hpp"
#include "terminalpp/ansi/csi.hpp"
#include "terminalpp/ansi/dec_private_mode.hpp"
#include "terminalpp/ansi/ss3.hpp"
#include "terminalpp/detail/lambda_visitor.hpp"
#include <algorithm>
#include <utility>

namespace terminalpp { namespace detail {

static vk_modifier convert_modifier_argument(std::string const &modifier)
{
    static constexpr std::pair<u8, vk_modifier> modifier_mappings[] = {
        { ansi::csi::MODIFIER_SHIFT,               vk_modifier::shift },
        { ansi::csi::MODIFIER_CTRL,                vk_modifier::ctrl  },
        { ansi::csi::MODIFIER_ALT,                 vk_modifier::alt   },
        { ansi::csi::MODIFIER_META,                vk_modifier::meta  },

        { ansi::csi::MODIFIER_SHIFT_ALT,           vk_modifier::shift
                                                 | vk_modifier::alt   },
        { ansi::csi::MODIFIER_SHIFT_CTRL,          vk_modifier::shift
                                                 | vk_modifier::ctrl  },
        { ansi::csi::MODIFIER_ALT_CTRL,            vk_modifier::alt
                                                 | vk_modifier::ctrl  },
        { ansi::csi::MODIFIER_SHIFT_ALT_CTRL,      vk_modifier::shift
                                                 | vk_modifier::alt
                                                 | vk_modifier::ctrl  },

        { ansi::csi::MODIFIER_META_SHIFT,          vk_modifier::meta
                                                 | vk_modifier::shift },
        { ansi::csi::MODIFIER_META_CTRL,           vk_modifier::meta
                                                 | vk_modifier::ctrl  },
        { ansi::csi::MODIFIER_META_ALT,            vk_modifier::meta
                                                 | vk_modifier::alt   },

        { ansi::csi::MODIFIER_META_SHIFT_ALT,      vk_modifier::meta
                                                 | vk_modifier::shift
                                                 | vk_modifier::alt   },
        { ansi::csi::MODIFIER_META_SHIFT_CTRL,     vk_modifier::meta
                                                 | vk_modifier::shift
                                                 | vk_modifier::ctrl  },
        { ansi::csi::MODIFIER_META_ALT_CTRL,       vk_modifier::meta
                                                 | vk_modifier::alt
                                                 | vk_modifier::ctrl  },
        { ansi::csi::MODIFIER_META_SHIFT_ALT_CTRL, vk_modifier::meta
                                                 | vk_modifier::shift
                                                 | vk_modifier::alt
                                                 | vk_modifier::ctrl  },
    };

    auto value = atoi(modifier.c_str());

    using std::begin;
    using std::end;

    auto mapping = std::find_if(
        begin(modifier_mappings),
        end(modifier_mappings),
        [value](auto const &mapping)
        {
            return mapping.first == value;
        });

    return mapping != end(modifier_mappings)
         ? mapping->second
         : vk_modifier::none;
}

static token convert_control_sequence(ansi::control_sequence const &seq)
{
    // Cursor Movement commands are in the form "ESC [ C" where C is some
    // letter indicating the direction in which to move.
    static std::vector<std::pair<char, vk>> const cursor_movement_commands = {
        { ansi::csi::CURSOR_UP,                  vk::cursor_up    },
        { ansi::csi::CURSOR_DOWN,                vk::cursor_down  },
        { ansi::csi::CURSOR_FORWARD,             vk::cursor_right },
        { ansi::csi::CURSOR_BACKWARD,            vk::cursor_left  },
        { ansi::csi::CURSOR_HOME,                vk::home         },
        { ansi::csi::CURSOR_TABULATION,          vk::ht           },
        { ansi::csi::CURSOR_BACKWARD_TABULATION, vk::bt           },
    };

    assert(seq.initiator == ansi::control7::CSI[1]);

    auto const &cursor_movement_command = std::find_if(
        cursor_movement_commands.begin(),
        cursor_movement_commands.end(),
        [&seq](auto const &elem)
        {
            return elem.first == seq.command;
        });

    auto repeat_count_arg = seq.arguments.empty()
                          ? std::string("1")
                          : seq.arguments[0];

    auto repeat_count = u8(std::max(atoi(repeat_count_arg.c_str()), 1));

    vk_modifier modifier = seq.meta
                         ? vk_modifier::meta
                         : vk_modifier::none;

    if (cursor_movement_command != cursor_movement_commands.end())
    {
        return virtual_key{
            cursor_movement_command->second,
            modifier,
            repeat_count,
            seq };
    }

    return seq;
}

static token convert_ss3_sequence(ansi::control_sequence const &seq)
{
    // SS3 commands are delivered as "ESC O C" where C is a letter designating
    // the command to perform.
    static std::vector<std::pair<char, vk>> const ss3_commands = {
        { ansi::ss3::CURSOR_UP,    vk::cursor_up    },
        { ansi::ss3::CURSOR_DOWN,  vk::cursor_down  },
        { ansi::ss3::CURSOR_RIGHT, vk::cursor_right },
        { ansi::ss3::CURSOR_LEFT,  vk::cursor_left  },
        { ansi::ss3::CURSOR_HOME,  vk::home         },
        { ansi::ss3::CURSOR_END,   vk::end          },
        { ansi::ss3::CURSOR_TAB,   vk::ht           },
        { ansi::ss3::ENTER,        vk::enter        },
        { ansi::ss3::F1,           vk::f1           },
        { ansi::ss3::F2,           vk::f2           },
        { ansi::ss3::F3,           vk::f3           },
        { ansi::ss3::F4,           vk::f4           },
    };

    assert(seq.initiator == ansi::control7::SS3[1]);

    auto const &ss3_command = std::find_if(
        ss3_commands.begin(),
        ss3_commands.end(),
        [&seq](auto const &elem)
        {
            return elem.first == seq.command;
        });

    if (ss3_command != ss3_commands.end())
    {
        vk_modifier modifier = seq.meta
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

static token convert_keypad_sequence(ansi::control_sequence const &seq)
{
    // Keypad commands are delivered as "ESC [ N ~" where N is a number
    // designating the key pressed.
    static std::vector<std::pair<u8, vk>> const keypad_commands = {
        { ansi::csi::KEYPAD_HOME,   vk::home },
        { ansi::csi::KEYPAD_INSERT, vk::ins  },
        { ansi::csi::KEYPAD_DEL,    vk::del  },
        { ansi::csi::KEYPAD_END,    vk::end  },
        { ansi::csi::KEYPAD_PGUP,   vk::pgup },
        { ansi::csi::KEYPAD_PGDN,   vk::pgdn },
        { ansi::csi::KEYPAD_F1,     vk::f1   },
        { ansi::csi::KEYPAD_F2,     vk::f2   },
        { ansi::csi::KEYPAD_F3,     vk::f3   },
        { ansi::csi::KEYPAD_F4,     vk::f4   },
        { ansi::csi::KEYPAD_F5,     vk::f5   },
        { ansi::csi::KEYPAD_F6,     vk::f6   },
        { ansi::csi::KEYPAD_F7,     vk::f7   },
        { ansi::csi::KEYPAD_F8,     vk::f8   },
        { ansi::csi::KEYPAD_F9,     vk::f9   },
        { ansi::csi::KEYPAD_F10,    vk::f10  },
        { ansi::csi::KEYPAD_F11,    vk::f11  },
        { ansi::csi::KEYPAD_F12,    vk::f12  },
    };

    assert(seq.command == ansi::csi::KEYPAD_FUNCTION);

    if (seq.arguments[0].empty() || !isdigit(seq.arguments[0][0]))
    {
        // Nothing will match.
        return seq;
    }

    auto argument = atoi(seq.arguments[0].c_str());
    auto keypad_command = std::find_if(
        keypad_commands.begin(),
        keypad_commands.end(),
        [argument](auto const &elem)
        {
            return argument == elem.first;
        });

    if (keypad_command != keypad_commands.end())
    {
        vk_modifier modifier = seq.arguments.size() > 1
                             ? convert_modifier_argument(seq.arguments[1])
                             : vk_modifier::none;

        if (seq.meta)
        {
            modifier |= vk_modifier::meta;
        }

        return virtual_key{
            keypad_command->second,
            modifier,
            1,
            seq };
    }

    return seq;
}

static token convert_common_control_sequence(ansi::control_sequence const &seq)
{
    if (seq.initiator == ansi::control7::CSI[1])
    {
        if (seq.command == ansi::csi::KEYPAD_FUNCTION)
        {
            return convert_keypad_sequence(seq);
        }

        return convert_control_sequence(seq);
    }
    else if (seq.initiator == ansi::control7::SS3[1])
    {
        return convert_ss3_sequence(seq);
    }

    return seq;
}

// ==========================================================================
// GET_WELL_KNOWN_VIRTUAL_KEY
// ==========================================================================
token get_well_known_virtual_key(token const &tok)
{
    return boost::apply_visitor(make_lambda_visitor<token>(
        [](ansi::control_sequence const &seq)
        {
            return convert_common_control_sequence(seq);
        },
        [](auto &&t)
        {
            return t;
        }),
        tok);
}

}}
