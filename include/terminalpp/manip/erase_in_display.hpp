#pragma once
#include "terminalpp/terminal.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief A structure that encapsulates a cursor restore operation
//* =========================================================================
struct erase_in_display
{
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    erase_in_display(terminal::erase_display how)
      : how_(how)
    {
    }

    //* =====================================================================
    /// \brief Restores the cursor in the terminal.
    //* =====================================================================
    std::string operator()(terminal &term)
    {
        return term.erase_in_display(how_);
    }

    terminal::erase_display how_;
};

}