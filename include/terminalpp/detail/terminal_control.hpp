#ifndef TERMINALPP_DETAIL_TERMINAL_CONTROL_HPP_
#define TERMINALPP_DETAIL_TERMINAL_CONTROL_HPP_

#include "terminalpp/terminal.hpp"
#include <string>

namespace terminalpp { namespace detail {

//* =========================================================================
/// \brief Returns the Command Sequence Introducer sequence
//* =========================================================================
std::string csi(terminalpp::terminal::control_mode const &control_mode);

}}

#endif
