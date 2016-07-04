#include "terminalpp/terminal.hpp"
#include "terminalpp/ansi/osc.hpp"
#include "terminalpp/detail/terminal_control.hpp"
#include "terminalpp/detail/terminal_cursor_control.hpp"
#include "terminalpp/detail/element_difference.hpp"
#include "terminalpp/detail/parser.hpp"
#include "terminalpp/detail/well_known_virtual_key.hpp"
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

// ==========================================================================
// REPLACE_WELL_KNOWN_VIRTUAL_KEYS
// ==========================================================================
std::vector<token> replace_well_known_virtual_keys(std::vector<token> tokens)
{
    std::transform(tokens.begin(), tokens.end(), tokens.begin(),
        detail::get_well_known_virtual_key);

    return tokens;
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
             + terminalpp::detail::ascii::BEL;
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
std::string terminal::move_cursor(point const &pos)
{
    std::string result;

    // Note: terminal uses 0-based co-ordinates whereas ANSI uses a
    // 1-based indexing.  Therefore, we need to offset the cursor position
    // in order to get the correct output when actually calling functions
    // that refer to co-ordinates (cursor_position and
    // cursor_horizontal_absolute).
    auto ansipos = pos + point{1, 1};

    if (cursor_position_)
    {
        // If we have a known cursor position, then we may be able to return a
        // shorter sequence, depending on the exact operation required.

        // If we're staying on the same line, then the following options are
        // available to us, if they are supported.
        //    * Cursor Horizontal Absolute (move to position on current line)
        //    * Cursor Forward
        //    * Cursor Backward
        if (*cursor_position_ == pos)
        {
            // Do nothing.
            return result;
        }

        if (cursor_position_->y == pos.y)
        {
            if (ansipos.x < 10 && behaviour_.supports_cha)
            {
                // Note: Cursor Horizontal Absolute uses 1-based indexing,
                // where terminal uses 0-based indexing.  Therefore, it needs
                // an offset.
                result =
                    detail::cursor_horizontal_absolute(
                        ansipos.x, behaviour_, control_mode_);
            }
            else
            {
                if (pos.x > cursor_position_->x)
                {
                    result =
                        detail::cursor_forward(
                            pos.x - cursor_position_->x,
                            control_mode_);
                }
                else
                {
                    result =
                        detail::cursor_backward(
                            cursor_position_->x - pos.x,
                            control_mode_);
                }
            }
        }
        else if (cursor_position_->x == pos.x)
        {
            if (cursor_position_->y > pos.y)
            {
                result = detail::cursor_up(cursor_position_->y - pos.y, control_mode_);
            }
            else
            {
                result = detail::cursor_down(pos.y - cursor_position_->y, control_mode_);
            }
        }
        else
        {
            // Since we must move in both dimensions, there's no short-cut
            // command to use.
            result = detail::cursor_position(ansipos, behaviour_, control_mode_);
        }
    }
    else
    {
        // The cursor position was unknown.  There are no shortcuts we can
        // sensibly take in this situation.
        result = detail::cursor_position(ansipos, behaviour_, control_mode_);
    }

    cursor_position_ = pos;

    return result;
}

// ==========================================================================
// READ
// ==========================================================================
std::vector<terminalpp::token> terminal::read(std::string const &data)
{
    std::vector<terminalpp::token> results;

    std::for_each(data.begin(), data.end(),
    [&](auto ch)
    {
        auto result = parser_(ch);

        if (result)
        {
            results.push_back(*result);
        }
    });

    // Some postprocessing for well-known control sequence->
    // virtual key mappings.
    return replace_well_known_virtual_keys(results);
}

// ==========================================================================
// WRITE
// ==========================================================================
std::string terminal::write(element const &elem)
{
    std::string result =
        detail::element_difference(last_element_, elem, behaviour_)
      + write_element(elem);

    if (cursor_position_)
    {
        ++(cursor_position_->x);

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

    last_element_ = elem;

    return result;
}

// ==========================================================================
// WRITE
// ==========================================================================
std::string terminal::write(string const& str)
{
    std::string result;

    std::for_each(str.begin(), str.end(),
        [&result, this](auto const &elem)
        {
            result += this->write(elem);
        });

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
