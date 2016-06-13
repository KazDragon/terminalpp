#pragma once

#include "terminalpp/terminal.hpp"
#include <string>

namespace terminalpp { namespace detail {

//* =========================================================================
/// \brief Returns the Command Sequence Introducer sequence
//* =========================================================================
std::string csi(terminalpp::terminal::control_mode const &control_mode);

//* =========================================================================
/// \brief Returns the Operating System Control sequence
//* =========================================================================
std::string osc(terminalpp::terminal::control_mode const &control_mode);

//* =========================================================================
/// \brief Returns the String Terminator sequence
//* =========================================================================
std::string st(terminalpp::terminal::control_mode const &control_mode);

}}
