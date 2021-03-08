#include "terminalpp/mouse.hpp"
#include <iostream>

namespace terminalpp { namespace mouse {

// ==========================================================================
// OPERATOR<<
// ==========================================================================
std::ostream &operator<<(std::ostream &out, event const &ev)
{
    out << "mouse_event["
        << ev.position_
        << ", ";

    switch(ev.action_)
    {
       case event_type::left_button_down :   out << "lmb"; break;
       case event_type::middle_button_down : out << "mmb"; break;
       case event_type::right_button_down :  out << "rmb"; break;
       case event_type::button_up :          out << "up"; break;
       case event_type::no_button_change :   out << "no-change"; break;
       case event_type::scrollwheel_down :   out << "sdn"; break;
       case event_type::scrollwheel_up :     out << "sup"; break;
       default : out << "unk"; break;
    }

    return out << "]";
}

}}
