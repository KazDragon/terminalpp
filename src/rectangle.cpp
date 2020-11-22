#include "terminalpp/rectangle.hpp"
#include <ostream>

namespace terminalpp {

std::ostream &operator<<(std::ostream &out, terminalpp::rectangle const &rect)
{
    return out << "rectangle(" << rect.origin << ", " << rect.size << ")";
}

}