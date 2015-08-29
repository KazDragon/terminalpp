#ifndef TERMINALPP_ANSI_MOUSE_HPP_
#define TERMINALPP_ANSI_MOUSE_HPP_

#include "terminalpp/core.hpp"

namespace terminalpp { namespace ansi { namespace mouse {
   
struct report
{
    static terminalpp::u8 const LEFT_BUTTON_DOWN   = terminalpp::u8(0);
    static terminalpp::u8 const MIDDLE_BUTTON_DOWN = terminalpp::u8(1);
    static terminalpp::u8 const RIGHT_BUTTON_DOWN  = terminalpp::u8(2);
    static terminalpp::u8 const BUTTON_UP          = terminalpp::u8(3);
    static terminalpp::u8 const SCROLLWHEEL_UP     = terminalpp::u8(32);
    static terminalpp::u8 const SCROLLWHEEL_DOWN   = terminalpp::u8(33);

    terminalpp::u8  button_;
    terminalpp::s32 x_position_;
    terminalpp::s32 y_position_;
};
    
constexpr inline bool operator==(report const &lhs, report const &rhs)
{
    return lhs.button_     == rhs.button_
        && lhs.x_position_ == rhs.x_position_
        && lhs.y_position_ == rhs.y_position_;
}

}}}

#endif
