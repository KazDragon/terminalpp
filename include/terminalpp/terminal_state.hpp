#pragma once

#include "terminalpp/detail/parser.hpp"
#include "terminalpp/element.hpp"
#include "terminalpp/extent.hpp"
#include "terminalpp/point.hpp"
#include <boost/optional.hpp>

namespace terminalpp {

//* =========================================================================
/// \brief The state of a terminal, which manipulators are allowed to use and
/// edit.
//* =========================================================================
struct TERMINALPP_EXPORT terminal_state
{
    terminal_state();

    extent                   terminal_size_;
    boost::optional<element> last_element_;
    boost::optional<point>   cursor_position_;
    boost::optional<point>   saved_cursor_position_;
    boost::optional<bool>    cursor_visible_;
    detail::parser           input_parser_;
};

}
