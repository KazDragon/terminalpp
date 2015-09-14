#include "terminalpp/terminal.hpp"
#include "terminalpp/ansi/control_characters.hpp"
#include "terminalpp/detail/element_difference.hpp"
#include "terminalpp/detail/write_element.hpp"

namespace terminalpp {

namespace {
    
// ==========================================================================
// CSI
// ==========================================================================
std::string csi(terminalpp::terminal::control_mode const &control_mode)
{
    return control_mode == terminalpp::terminal::control_mode::seven_bit
                         ? terminalpp::ansi::control7::CSI
                         : terminalpp::ansi::control8::CSI;
}

// ==========================================================================
// CURSOR_UP
// ==========================================================================
std::string cursor_up(
    s32                                       y,
    terminalpp::terminal::control_mode const &control_mode)
{
    std::string result = csi(control_mode);
    
    // If y is 1, then we can skip the amount indicator.  Note: Pretty much
    // anything that supports CUA supports the default, so this isn't checked
    // in the behaviour.
    if (y != 1)
    {
        result += std::to_string(y);
    }
    
    result += terminalpp::ansi::csi::CURSOR_UP;
    
    return result;
}

// ==========================================================================
// CURSOR_UP
// ==========================================================================
std::string cursor_down(
    s32                                       y,
    terminalpp::terminal::control_mode const &control_mode)
{
    std::string result = csi(control_mode);
    
    // If y is 1, then we can skip the amount indicator.  Note: Pretty much
    // anything that supports CUB supports the default, so this isn't checked
    // in the behaviour.
    if (y != 1)
    {
        result += std::to_string(y);
    }
    
    result += terminalpp::ansi::csi::CURSOR_DOWN;
    
    return result;
}

// ==========================================================================
// CURSOR_FORWARD
// ==========================================================================
std::string cursor_forward(
    s32                           x,
    terminal::control_mode const &control_mode)
{
    std::string result = csi(control_mode);
    
    // If x is 1, then we can skip the amount indicator.  Note: Pretty much
    // anything that supports CUF supports the default, so this isn't checked
    // in the behaviour.
    if (x != 1)
    {
        result += std::to_string(x);
    }
    
    result += terminalpp::ansi::csi::CURSOR_FORWARD;
    
    return result;
}

// ==========================================================================
// CURSOR_BACKWARD
// ==========================================================================
std::string cursor_backward(
    s32                           x,
    terminal::control_mode const &control_mode)
{
    std::string result = csi(control_mode);
    
    // If x is 1, then we can skip the amount indicator.  Note: Pretty much
    // anything that supports CUB supports the default, so this isn't checked
    // in the behaviour.
    if (x != 1)
    {
        result += std::to_string(x);
    }
    
    result += terminalpp::ansi::csi::CURSOR_BACKWARD;
    
    return result;
}

// ==========================================================================
// CURSOR_HORIZONTAL_ABSOLUTE
// ==========================================================================
std::string cursor_horizontal_absolute(
    s32                           x, 
    terminal::behaviour const    &behaviour,
    terminal::control_mode const &control_mode)
{
    std::string result;
    
    result += csi(control_mode);
    
    // If x is 1, and our terminal supports CHA with a default argument, then
    // we can skip the character the column indicator.  Otherwise, we have to
    // include it.
    if (x != 1 || !behaviour.supports_cha_default)
    {
        result += std::to_string(x);
    }
    
    result += terminalpp::ansi::csi::CURSOR_HORIZONTAL_ABSOLUTE;
    
    return result;
}

// ==========================================================================
// CURSOR_POSITION
// ==========================================================================
std::string cursor_position(
    point                  const &pt,
    terminal::behaviour    const &behaviour,
    terminal::control_mode const &control_mode)
{
    return csi(control_mode)
         + std::to_string(pt.y)
         + terminalpp::ansi::PS
         + std::to_string(pt.x)
         + terminalpp::ansi::csi::CURSOR_POSITION;
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
// SHOW_CURSOR
// ==========================================================================
std::string terminal::show_cursor()
{
    if (cursor_mode_ != cursor_mode::shown)
    {
        cursor_mode_ = cursor_mode::shown;
        
        return csi(control_mode_)
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
        
        return csi(control_mode_)
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

    return csi(control_mode_)
         + terminalpp::ansi::csi::SAVE_CURSOR_POSITION;
}

// ==========================================================================
// RESTORE_CURSOR
// ==========================================================================
std::string terminal::restore_cursor()
{
    cursor_position_ = saved_cursor_position_;

    return csi(control_mode_)
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
                    cursor_horizontal_absolute(
                        pt.x, behaviour_, control_mode_);
            }
            else
            {
                if (pt.x > cursor_position_->x)
                {
                    result =
                        cursor_forward(
                            pt.x - cursor_position_->x,
                            control_mode_);
                }
                else
                {
                    result =
                        cursor_backward(
                            cursor_position_->x - pt.x,
                            control_mode_);
                }
            }
        }
        else if (cursor_position_->x == pt.x)
        {
            if (cursor_position_->y > pt.y)
            {
                result = cursor_up(cursor_position_->y - pt.y, control_mode_);
            }
            else
            {
                result = cursor_down(pt.y - cursor_position_->y, control_mode_);
            }
        }
        else
        {
            // Since we must move in both dimensions, there's no short-cut
            // command to use.
            result = cursor_position(pt, behaviour_, control_mode_);
        }
    }
    else
    {
        // The cursor position was unknown.  There are no shortcuts we can
        // sensibly take in this situation.
        result = cursor_position(pt, behaviour_, control_mode_);
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
        result += detail::write_element(elem);

        last_element_ = elem;
    }
    
    return result;
}


}
