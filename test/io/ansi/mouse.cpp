#include "terminalpp/ansi/mouse.hpp"
#include <iostream>

namespace terminalpp { namespace ansi { namespace mouse {

std::ostream &operator<<(std::ostream &out, report const &mr)
{
    return out << "mouse::report[button=" << int(mr.button_)
               << ", pos=(" << mr.x_position_ << "," << mr.y_position_ << ")]";
}

}}}