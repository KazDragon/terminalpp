#include "terminalpp/ansi/mouse.hpp"
#include <iostream>

namespace terminalpp { namespace ansi { namespace mouse {

constexpr byte const report::LEFT_BUTTON_DOWN;
constexpr byte const report::MIDDLE_BUTTON_DOWN;
constexpr byte const report::RIGHT_BUTTON_DOWN;
constexpr byte const report::BUTTON_UP;
constexpr byte const report::NO_BUTTON_CHANGE;
constexpr byte const report::SCROLLWHEEL_UP;
constexpr byte const report::SCROLLWHEEL_DOWN;

// ==========================================================================
// OPERATOR<<
// ==========================================================================
std::ostream &operator<<(std::ostream &out, report const &rep)
{
    out << "mouse_report["
        << rep.x_position_
        << ", "
        << rep.y_position_
        << ", ";

    switch(rep.button_)
    {
       case report::LEFT_BUTTON_DOWN :   out << "lmb"; break;
       case report::MIDDLE_BUTTON_DOWN : out << "mmb"; break;
       case report::RIGHT_BUTTON_DOWN :  out << "rmb"; break;
       case report::BUTTON_UP :          out << "up"; break;
       case report::NO_BUTTON_CHANGE :   out  << "no-change"; break;
       case report::SCROLLWHEEL_DOWN :   out << "sdn"; break;
       case report::SCROLLWHEEL_UP :     out << "sup"; break;
       default : out << "unk"; break;
    }

    return out << "]";
}

}}}

