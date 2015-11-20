#ifndef TERMINALPP_TOKEN_HPP_
#define TERMINALPP_TOKEN_HPP_

#include "terminalpp/ansi/control_sequence.hpp"
#include "terminalpp/ansi/mouse.hpp"
#include "terminalpp/virtual_key.hpp"
#include <boost/variant.hpp>

namespace terminalpp {

using token = boost::variant<
    terminalpp::virtual_key,
    terminalpp::ansi::mouse::report,
    terminalpp::ansi::control_sequence
>;

}

#endif