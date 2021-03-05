#pragma once

#include "terminalpp/core.hpp"
#include "terminalpp/control_sequence.hpp"
#include "terminalpp/mouse.hpp"
#include "terminalpp/virtual_key.hpp"
#include <boost/variant.hpp>
#include <vector>

namespace terminalpp {

using token = boost::variant<
    terminalpp::virtual_key,
    terminalpp::mouse::event,
    terminalpp::control_sequence
>;

using tokens = gsl::span<token const>;
using token_storage = std::vector<token>;

}
