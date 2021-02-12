#include "terminalpp/detail/terminal_control.hpp"
#include "terminalpp/ansi/control_characters.hpp"

namespace terminalpp { namespace detail {

// ==========================================================================
// CSI
// ==========================================================================
byte_storage csi(control_mode const &mode)
{
    return mode == control_mode::seven_bit
         ? terminalpp::ansi::control7::CSI
         : terminalpp::ansi::control8::CSI;
}

// ==========================================================================
// OSC
// ==========================================================================
byte_storage osc(control_mode const &mode)
{
    return mode == control_mode::seven_bit
         ? terminalpp::ansi::control7::OSC
         : terminalpp::ansi::control8::OSC;
}

// ==========================================================================
// ST
// ==========================================================================
byte_storage st(control_mode const &mode)
{
    return mode == control_mode::seven_bit
         ? terminalpp::ansi::control7::ST
         : terminalpp::ansi::control8::ST;
}

}}
