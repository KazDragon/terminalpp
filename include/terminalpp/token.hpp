#pragma once

#include "terminalpp/control_sequence.hpp"
#include "terminalpp/mouse.hpp"
#include "terminalpp/virtual_key.hpp"

#include <span>
#include <variant>
#include <vector>

namespace terminalpp {

using token = std::variant<
    terminalpp::virtual_key,
    terminalpp::mouse::event,
    terminalpp::control_sequence>;

using tokens = std::span<token const>;
using token_storage = std::vector<token>;

}  // namespace terminalpp
