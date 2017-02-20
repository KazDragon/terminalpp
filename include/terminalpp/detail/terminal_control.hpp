#pragma once

#include "terminalpp/terminal.hpp"
#include <string>

namespace terminalpp { namespace detail {

enum class control_mode
{
    seven_bit,
    eight_bit,
};

//* =========================================================================
/// \brief Returns the Command Sequence Introducer sequence
//* =========================================================================
std::string csi(control_mode const &mode);

//* =========================================================================
/// \brief Returns the Operating System Control sequence
//* =========================================================================
std::string osc(control_mode const &mode);

//* =========================================================================
/// \brief Returns the String Terminator sequence
//* =========================================================================
std::string st(control_mode const &mode);

}}
