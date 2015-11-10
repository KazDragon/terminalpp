#include "terminalpp/terminal.hpp"
#include "terminalpp/ansi/control_characters.hpp"
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

static token convert_control_sequence(ansi::control_sequence const &seq)
{
    // Cursor Movement commands are in the form "ESC [ C" where C is some
    // letter indicating the direction in which to move.
    static std::vector<std::pair<char, char>> const cursor_movement_commands = {
        { ansi::csi::CURSOR_UP,       VK_UP    },
        { ansi::csi::CURSOR_DOWN,     VK_DOWN  },
        { ansi::csi::CURSOR_FORWARD,  VK_RIGHT },
        { ansi::csi::CURSOR_BACKWARD, VK_LEFT  },
        { ansi::csi::CURSOR_HOME,     VK_HOME  },
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
        return virtual_key{ cursor_movement_command->second, 0, 1, seq };
    }

    return seq;
}

static token convert_ss3_sequence(ansi::control_sequence const &seq)
{
    // SS3 commands are delivered as "ESC O C" where C is a letter designating
    // the command to perform.
    static std::vector<std::pair<char, char>> const ss3_commands = {
        { ansi::ss3::CURSOR_UP,    VK_UP    },
        { ansi::ss3::CURSOR_DOWN,  VK_DOWN  },
        { ansi::ss3::CURSOR_RIGHT, VK_RIGHT },
        { ansi::ss3::CURSOR_LEFT,  VK_LEFT  },
        { ansi::ss3::CURSOR_HOME,  VK_HOME  },
        { ansi::ss3::CURSOR_END,   VK_END   },
        { ansi::ss3::F1,           VK_F1    },
        { ansi::ss3::F2,           VK_F2    },
        { ansi::ss3::F3,           VK_F3    },
        { ansi::ss3::F4,           VK_F4    },
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
        return virtual_key{ ss3_command->second, 0, 1, seq };
    }

    return seq;
}

static token convert_keypad_sequence(ansi::control_sequence const &seq)
{
    // Keypad commands are delivered as "ESC [ N ~" where N is a number
    // designating the key pressed.
    static std::vector<std::pair<u8, char>> const keypad_commands = {
        { ansi::csi::KEYPAD_HOME,   VK_HOME },
        { ansi::csi::KEYPAD_INSERT, VK_INS  },
        { ansi::csi::KEYPAD_DEL,    VK_DEL  },
        { ansi::csi::KEYPAD_END,    VK_END  },
        { ansi::csi::KEYPAD_PGUP,   VK_PGUP },
        { ansi::csi::KEYPAD_PGDN,   VK_PGDN },
        { ansi::csi::KEYPAD_F1,     VK_F1   },
        { ansi::csi::KEYPAD_F2,     VK_F2   },
        { ansi::csi::KEYPAD_F3,     VK_F3   },
        { ansi::csi::KEYPAD_F4,     VK_F4   },
        { ansi::csi::KEYPAD_F5,     VK_F5   },
        { ansi::csi::KEYPAD_F6,     VK_F6   },
        { ansi::csi::KEYPAD_F7,     VK_F7   },
        { ansi::csi::KEYPAD_F8,     VK_F8   },
        { ansi::csi::KEYPAD_F9,     VK_F9   },
        { ansi::csi::KEYPAD_F10,    VK_F10  },
        { ansi::csi::KEYPAD_F11,    VK_F11  },
        { ansi::csi::KEYPAD_F12,    VK_F12  },
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
        return virtual_key{ keypad_command->second, 0, 1, seq };
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
