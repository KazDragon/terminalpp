#include "terminalpp/terminal.hpp"
#include "terminalpp/ansi/control_characters.hpp"

namespace terminalpp {


// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
terminal::terminal(terminal::behaviour const &behaviour)
  : behaviour_(behaviour),
    control_mode_(control_mode::seven_bit)
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
        if (cursor_position_->y == pt.y)
        {
            if (pt.x == 1)
            {
                result += terminalpp::ansi::control7::CSI;
             
                if (behaviour_.supports_cha)
                {
                    if (!behaviour_.supports_cha_default)
                    {
                        result += '1';
                    }
                    
                    result += terminalpp::ansi::csi::CURSOR_HORIZONTAL_ABSOLUTE;
                }
                else
                {
                    result += std::to_string(cursor_position_->y - 1)
                            + terminalpp::ansi::csi::CURSOR_BACKWARD;
                }
            }
        }
    }
    else
    {
        result += terminalpp::ansi::control7::CSI
                + std::to_string(pt.x)
                + terminalpp::ansi::PS
                + std::to_string(pt.y)
                + terminalpp::ansi::csi::CURSOR_POSITION;
    }
    
    cursor_position_ = pt;

    return result;
}


}
