#pragma once

#include "terminalpp/control_sequence.hpp"
#include "terminalpp/core.hpp"
#include "terminalpp/mouse.hpp"
#include "terminalpp/virtual_key.hpp"
#include <variant>
#include <vector>

namespace terminalpp {

using token = std::variant<
    terminalpp::virtual_key,
    terminalpp::mouse::event,
    terminalpp::control_sequence>;

using tokens = gsl::span<token const>;
using token_storage = std::vector<token>;

}  // namespace terminalpp
