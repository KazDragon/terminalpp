#include "terminalpp/terminal.hpp"
#include "terminalpp/ansi/control_characters.hpp"
#include "terminalpp/detail/terminal_control.hpp"
#include "terminalpp/detail/terminal_cursor_control.hpp"
#include "terminalpp/detail/element_difference.hpp"

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
