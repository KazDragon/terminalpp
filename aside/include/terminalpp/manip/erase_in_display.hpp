#pragma once
#include "terminalpp/terminal.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief A structure that encapsulates an erase in display operation
//* =========================================================================
struct erase_in_display
{
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    constexpr explicit erase_in_display(terminal::erase_display how)
      : how_(how)
    {
    }

    //* =====================================================================
    /// \brief Erases some of the display of the terminal.
    //* =====================================================================
    std::string operator()(terminal &term)
    {
        return term.erase_in_display(how_);
    }

    terminal::erase_display how_;
};

}
