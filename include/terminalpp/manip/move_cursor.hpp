#pragma once
#include "terminalpp/terminal.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief A structure that encapsulates a cursor move operation
//* =========================================================================
struct move_cursor
{
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    constexpr move_cursor(terminalpp::point position)
      : position_(position)
    {
    }

    //* =====================================================================
    /// \brief Moves the cursor in the terminal.
    //* =====================================================================
    std::string operator()(terminal &term)
    {
        return term.move_cursor(position_);
    }

    terminalpp::point position_;
};

}