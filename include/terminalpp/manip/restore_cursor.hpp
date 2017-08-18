#pragma once
#include "terminalpp/terminal.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief A structure that encapsulates a cursor restore operation
//* =========================================================================
struct restore_cursor
{
    //* =====================================================================
    /// \brief Restores the cursor in the terminal.
    //* =====================================================================
    std::string operator()(terminal &term)
    {
        return term.restore_cursor();
    }
};

}