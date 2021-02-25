#pragma once
#include "terminalpp/terminal.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief A structure that encapsulates a cursor save operation
//* =========================================================================
struct save_cursor
{
    //* =====================================================================
    /// \brief Saves the cursor in the terminal.
    //* =====================================================================
    std::string operator()(terminal &term)
    {
        return term.save_cursor();
    }
};

}
