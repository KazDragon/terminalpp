#pragma once

#include "terminalpp/core.hpp"
#include "terminalpp/control_sequence.hpp"
#include "terminalpp/mouse.hpp"
#include "terminalpp/virtual_key.hpp"
#include <vector>
#include <variant>

namespace terminalpp {

using token = std::variant<
    terminalpp::virtual_key,
    terminalpp::mouse::event,
    terminalpp::control_sequence
>;

using tokens = gsl::span<token const>;
using token_storage = std::vector<token>;

}
