#pragma once

#include "terminalpp/detail/parser.hpp"
#include "terminalpp/element.hpp"
#include "terminalpp/extent.hpp"
#include "terminalpp/point.hpp"

#include <optional>

namespace terminalpp {

//* =========================================================================
/// \brief The state of a terminal, which manipulators are allowed to use and
/// edit.
//* =========================================================================
struct TERMINALPP_EXPORT terminal_state
{
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    terminal_state();

    /// \brief The sized of the terminal.
    extent terminal_size_;

    /// \brief The last element that was written to the terminal.
    std::optional<element> last_element_;

    /// \brief The current cursor position, if known.
    std::optional<point> cursor_position_;

    /// \brief The cursor position at which the last "save cursor position"
    /// command was executed.
    std::optional<point> saved_cursor_position_;

    /// \brief Whether the cursor is visible or not.
    std::optional<bool> cursor_visible_;

    /// \brief A parser for reading input.
    detail::parser input_parser_;
};

}  // namespace terminalpp
