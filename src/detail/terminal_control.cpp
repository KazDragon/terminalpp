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

}}
