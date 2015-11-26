#include "terminalpp/detail/terminal_control.hpp"

namespace terminalpp { namespace detail {

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
// OSC
// ==========================================================================
std::string osc(terminalpp::terminal::control_mode const &control_mode)
{
    return control_mode == terminalpp::terminal::control_mode::seven_bit
         ? terminalpp::ansi::control7::OSC
         : terminalpp::ansi::control8::OSC;
}

// ==========================================================================
// ST
// ==========================================================================
std::string st(terminalpp::terminal::control_mode const &control_mode)
{
    return control_mode == terminalpp::terminal::control_mode::seven_bit
         ? terminalpp::ansi::control7::ST
         : terminalpp::ansi::control8::ST;
}

}}
