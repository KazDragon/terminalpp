#include "terminalpp/terminal.hpp"
#include "terminalpp/ansi/control_characters.hpp"
#include "terminalpp/ansi/dec_private_mode.hpp"
#include "terminalpp/ansi/osc.hpp"
#include "terminalpp/ansi/ss3.hpp"
#include "terminalpp/detail/terminal_control.hpp"
#include "terminalpp/detail/terminal_cursor_control.hpp"
#include "terminalpp/detail/element_difference.hpp"
#include "terminalpp/detail/parser.hpp"
#include <cassert>

namespace terminalpp {

namespace {

// ==========================================================================
// WRITE_ELEMENT
// ==========================================================================
std::string write_element(const element& elem)
{
    std::string text;

    if (elem.glyph_.charset_ == terminalpp::ansi::charset::utf8)
    {
        for (size_t index = 0;
             index < sizeof(elem.glyph_.ucharacter_)
          && elem.glyph_.ucharacter_[index] != '\0';
             ++index)
        {
            text += elem.glyph_.ucharacter_[index];

            if (!(elem.glyph_.ucharacter_[index] & 0x80))
            {
                break;
            }
        }
    }
    else
    {
        text += elem.glyph_.character_;
    }

    return text;
}

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

    if (cursor_movement_command != cursor_movement_commands.end())
    {
        return virtual_key{
            cursor_movement_command->second,
            vk_modifier::none,
            1,
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
        return virtual_key{
            ss3_command->second,
            vk_modifier::none,
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

    auto const &keypad_command = std::find_if(
        keypad_commands.begin(),
        keypad_commands.end(),
        [&seq](auto const &elem)
        {
            return !seq.arguments[0].empty()
                && isdigit(seq.arguments[0][0])
                && atoi(seq.arguments[0].c_str()) == elem.first;
        });

    if (keypad_command != keypad_commands.end())
    {
        vk_modifier modifier = seq.arguments.size() > 1
                             ? convert_modifier_argument(seq.arguments[1])
                             : vk_modifier::none;

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

struct well_known_virtual_key_visitor : boost::static_visitor<token>
{
    template <class T>
    token operator()(T const &t) const
    {
        return t;
    }

    token operator()(ansi::control_sequence const &seq)
    {
        return convert_common_control_sequence(seq);
    }
};

// ==========================================================================
// REPLACE_WELL_KNOWN_VIRTUAL_KEYS
// ==========================================================================
std::vector<token> replace_well_known_virtual_keys(
    std::vector<token> const &orig)
{
    std::vector<token> replaced;
    well_known_virtual_key_visitor visitor;

    for (auto &&tok : orig)
    {
        replaced.push_back(boost::apply_visitor(visitor, tok));
    }

    return replaced;
}

}

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
terminal::terminal(terminal::behaviour const &behaviour)
  : behaviour_(behaviour)
{
}

// ==========================================================================
// INIT
// ==========================================================================
std::string terminal::init()
{
    std::string result;

    if (behaviour_.can_use_eight_bit_control_codes
     && !behaviour_.uses_eight_bit_control_codes_by_default)
    {
        result += terminalpp::ansi::control8::ENABLE;
    }

    return result;
}

// ==========================================================================
// ENABLE_MOUSE
// ==========================================================================
std::string terminal::enable_mouse()
{
    std::string result;

    if (behaviour_.supports_all_mouse_motion_tracking)
    {
        result += detail::csi(control_mode_)
                + ansi::DEC_PRIVATE_MODE
                + ansi::dec_pm::ALL_MOTION_MOUSE_TRACKING
                + ansi::dec_pm::SET;
    }
    else if (behaviour_.supports_basic_mouse_tracking)
    {
        result += detail::csi(control_mode_)
                + ansi::DEC_PRIVATE_MODE
                + ansi::dec_pm::BASIC_MOUSE_TRACKING
                + ansi::dec_pm::SET;
    }

    return result;
}

// ==========================================================================
// SET_WINDOW_TITLE
// ==========================================================================
std::string terminal::set_window_title(std::string const &title)
{
    if (behaviour_.supports_window_title_bel)
    {
        return detail::osc(control_mode_)
             + ansi::osc::SET_WINDOW_TITLE
             + ansi::PS
             + title
             + ascii::BEL;
    }

    if (behaviour_.supports_window_title_st)
    {
        return detail::osc(control_mode_)
             + ansi::osc::SET_WINDOW_TITLE
             + ansi::PS
             + title
             + detail::st(control_mode_);
    }

    return {};
}

// ==========================================================================
// SET_SIZE
// ==========================================================================
void terminal::set_size(const extent& size)
{
    size_ = size;
}


// ==========================================================================
// SHOW_CURSOR
// ==========================================================================
std::string terminal::show_cursor()
{
    if (cursor_mode_ != cursor_mode::shown)
    {
        cursor_mode_ = cursor_mode::shown;

        return detail::csi(control_mode_)
             + terminalpp::ansi::DEC_PRIVATE_MODE
             + terminalpp::ansi::dec_pm::CURSOR
             + terminalpp::ansi::dec_pm::SET;
    }
    else
    {
        return {};
    }
}

// ==========================================================================
// HIDE_CURSOR
// ==========================================================================
std::string terminal::hide_cursor()
{
    if (cursor_mode_ != cursor_mode::hidden)
    {
        cursor_mode_ = cursor_mode::hidden;

        return detail::csi(control_mode_)
             + terminalpp::ansi::DEC_PRIVATE_MODE
             + terminalpp::ansi::dec_pm::CURSOR
             + terminalpp::ansi::dec_pm::RESET;
    }
    else
    {
        return {};
    }
}

// ==========================================================================
// SAVE_CURSOR
// ==========================================================================
std::string terminal::save_cursor()
{
    saved_cursor_position_ = cursor_position_;

    return detail::csi(control_mode_)
         + terminalpp::ansi::csi::SAVE_CURSOR_POSITION;
}

// ==========================================================================
// RESTORE_CURSOR
// ==========================================================================
std::string terminal::restore_cursor()
{
    cursor_position_ = saved_cursor_position_;

    return detail::csi(control_mode_)
         + terminalpp::ansi::csi::RESTORE_CURSOR_POSITION;
}

// ==========================================================================
// MOVE_CURSOR
// ==========================================================================
std::string terminal::move_cursor(point const &pt)
{
    std::string result;

    if (cursor_position_)
    {
        // If we have a known cursor position, then we may be able to return a
        // shorter sequence, depending on the exact operation required.

        // If we're staying on the same line, then the following options are
        // available to us, if they are supported.
        //    * Cursor Horizontal Absolute (move to position on current line)
        //    * Cursor Forward
        //    * Cursor Backward
        if (*cursor_position_ == pt)
        {
            // Do nothing.
            return result;
        }

        if (cursor_position_->y == pt.y)
        {
            if (pt.x < 10 && behaviour_.supports_cha)
            {
                result =
                    detail::cursor_horizontal_absolute(
                        pt.x, behaviour_, control_mode_);
            }
            else
            {
                if (pt.x > cursor_position_->x)
                {
                    result =
                        detail::cursor_forward(
                            pt.x - cursor_position_->x,
                            control_mode_);
                }
                else
                {
                    result =
                        detail::cursor_backward(
                            cursor_position_->x - pt.x,
                            control_mode_);
                }
            }
        }
        else if (cursor_position_->x == pt.x)
        {
            if (cursor_position_->y > pt.y)
            {
                result = detail::cursor_up(cursor_position_->y - pt.y, control_mode_);
            }
            else
            {
                result = detail::cursor_down(pt.y - cursor_position_->y, control_mode_);
            }
        }
        else
        {
            // Since we must move in both dimensions, there's no short-cut
            // command to use.
            result = detail::cursor_position(pt, behaviour_, control_mode_);
        }
    }
    else
    {
        // The cursor position was unknown.  There are no shortcuts we can
        // sensibly take in this situation.
        result = detail::cursor_position(pt, behaviour_, control_mode_);
    }

    cursor_position_ = pt;

    return result;
}

// ==========================================================================
// READ
// ==========================================================================
std::vector<terminalpp::token> terminal::read(std::string const &data)
{
    unparsed_buffer_.insert(
        unparsed_buffer_.end(),
        data.begin(),
        data.end());

    auto begin = unparsed_buffer_.begin();
    auto result = detail::parse(begin, unparsed_buffer_.end());

    unparsed_buffer_.erase(unparsed_buffer_.begin(), begin);

    // Some postprocessing for well-known control sequence->
    // virtual key mappings.
    return replace_well_known_virtual_keys(result);
}

// ==========================================================================
// WRITE
// ==========================================================================
std::string terminal::write(string const& str)
{
    std::string result;

    for (auto &&elem : str)
    {
        result += detail::element_difference(last_element_, elem);
        result += write_element(elem);

        last_element_ = elem;
    }

    if (cursor_position_)
    {
        cursor_position_->x += str.size();

        if (size_)
        {
            while (cursor_position_->x > size_->width)
            {
                cursor_position_->x -= size_->width;

                if (cursor_position_->y < size_->height)
                {
                    ++cursor_position_->y;
                }
            }
        }
    }

    return result;
}

// ==========================================================================
// ERASE_IN_DISPLAY
// ==========================================================================
std::string terminal::erase_in_display(terminal::erase_display how)
{
    std::string result;

    result = detail::csi(control_mode_);

    switch (how)
    {
        default :
            // Fall-through
        case terminal::erase_display::all :
            result += terminalpp::ansi::csi::ERASE_IN_DISPLAY_ALL;
            break;

        case terminal::erase_display::above :
            result += terminalpp::ansi::csi::ERASE_IN_DISPLAY_ABOVE;
            break;

        case terminal::erase_display::below :
            result += terminalpp::ansi::csi::ERASE_IN_DISPLAY_BELOW;
            break;
    }

    result += terminalpp::ansi::csi::ERASE_IN_DISPLAY;

    return result;
}

// ==========================================================================
// ERASE_IN_LINE
// ==========================================================================
std::string terminal::erase_in_line(terminal::erase_line how)
{
    std::string result;

    result = detail::csi(control_mode_);

    switch (how)
    {
        default :
            // Fall-through
        case terminal::erase_line::all :
            result += terminalpp::ansi::csi::ERASE_IN_LINE_ALL;
            break;

        case terminal::erase_line::left :
            result += terminalpp::ansi::csi::ERASE_IN_LINE_LEFT;
            break;

        case terminal::erase_line::right :
            result += terminalpp::ansi::csi::ERASE_IN_LINE_RIGHT;
            break;
    }

    result += terminalpp::ansi::csi::ERASE_IN_LINE;

    return result;
}


}
