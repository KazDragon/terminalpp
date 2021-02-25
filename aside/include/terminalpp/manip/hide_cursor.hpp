#pragma once
#include "terminalpp/terminal.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief A structure that encapsulates a cursor hide operation
//* =========================================================================
struct hide_cursor
{
    //* =====================================================================
    /// \brief Hides the cursor in the terminal.
    //* =====================================================================
    std::string operator()(terminal &term)
    {
        return term.hide_cursor();
    }
};

}
