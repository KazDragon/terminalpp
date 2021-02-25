#pragma once

#include "terminalpp/core.hpp"

namespace terminalpp { namespace detail {

enum class control_mode
{
    seven_bit,
    eight_bit,
};

//* =========================================================================
/// \brief Returns the Command Sequence Introducer sequence
//* =========================================================================
byte_storage csi(control_mode const &mode);

//* =========================================================================
/// \brief Returns the Operating System Control sequence
//* =========================================================================
byte_storage osc(control_mode const &mode);

//* =========================================================================
/// \brief Returns the String Terminator sequence
//* =========================================================================
byte_storage st(control_mode const &mode);

}}
