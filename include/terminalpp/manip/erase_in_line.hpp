#pragma once
#include "terminalpp/terminal.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief A structure that encapsulates a cursor restore operation
//* =========================================================================
struct erase_in_line
{
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    constexpr explicit erase_in_line(terminal::erase_line how)
      : how_(how)
    {
    }

    //* =====================================================================
    /// \brief Restores the cursor in the terminal.
    //* =====================================================================
    std::string operator()(terminal &term)
    {
        return term.erase_in_line(how_);
    }

    terminal::erase_line how_;
};

}
