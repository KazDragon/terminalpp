#include "terminalpp/terminal.hpp"
#include "terminalpp/ansi/control_characters.hpp"

namespace terminalpp {

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
    
}
