#ifndef TERMINALPP_DETAIL_PARSE_HELPER_HPP_
#define TERMINALPP_DETAIL_PARSE_HELPER_HPP_

#include "terminalpp/token.hpp"
#include <vector>

namespace terminalpp { namespace detail {

enum class state
{
    idle,
    escape,
    arguments,
};

struct parse_temps
{
    state state_;
    char initialiser_;
    bool meta_;
    terminalpp::u32 argument_;
    std::vector<terminalpp::u32> arguments_;
};

boost::optional<terminalpp::token> parse_helper(char input, parse_temps &temps);

}}

#endif
