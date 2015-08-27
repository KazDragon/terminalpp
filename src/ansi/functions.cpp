#include "terminalpp/ansi/functions.hpp"
#include "terminalpp/ansi/protocol.hpp"
#include <cstring>

namespace terminalpp { namespace ansi {

namespace {

std::string move_cursor(terminalpp::u8 amount, char direction)
{
    if (amount == 1)
    {
        return std::string {
            ESCAPE,
            CONTROL_SEQUENCE_INTRODUCER,
            direction
        };
    }
    else
    {
        static char const format_str[] = "%c%c%d%c";
        char str[7];
        sprintf(
            str, 
            format_str, 
            ESCAPE, 
            CONTROL_SEQUENCE_INTRODUCER, 
            u32(amount),
            direction);
        return str;
    }
}
    
}

// Cursor Movement and Control
std::string move_cursor_up(terminalpp::u8 amount)
{
    return move_cursor(amount, CURSOR_UP);
}

std::string move_cursor_down(terminalpp::u8 amount)
{
    return move_cursor(amount, CURSOR_DOWN);
}

std::string move_cursor_forward(terminalpp::u8 amount)
{
    return move_cursor(amount, CURSOR_FORWARD);
}

std::string move_cursor_backward(terminalpp::u8 amount)
{
    return move_cursor(amount, CURSOR_BACKWARD);
}

std::string move_cursor_to_column(terminalpp::u8 amount)
{
    return move_cursor(amount, CURSOR_HORIZONTAL_ABSOLUTE);
}

}}
