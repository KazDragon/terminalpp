#include "terminalpp/detail/terminal_control.hpp"
#include "terminalpp/ansi/control_characters.hpp"

namespace terminalpp { namespace detail {

// ==========================================================================
// CSI
// ==========================================================================
std::string csi(control_mode const &mode)
{
    return mode == control_mode::seven_bit
         ? terminalpp::ansi::control7::CSI
         : terminalpp::ansi::control8::CSI;
}

// ==========================================================================
// OSC
// ==========================================================================
std::string osc(control_mode const &mode)
{
    return mode == control_mode::seven_bit
         ? terminalpp::ansi::control7::OSC
         : terminalpp::ansi::control8::OSC;
}

// ==========================================================================
// ST
// ==========================================================================
std::string st(control_mode const &mode)
{
    return mode == control_mode::seven_bit
         ? terminalpp::ansi::control7::ST
         : terminalpp::ansi::control8::ST;
}

}}
