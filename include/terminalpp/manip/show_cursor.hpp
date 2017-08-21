#pragma once
#include "terminalpp/terminal.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief A structure that encapsulates a cursor show operation
//* =========================================================================
struct show_cursor
{
    //* =====================================================================
    /// \brief Shows the cursor in the terminal.
    //* =====================================================================
    std::string operator()(terminal &term)
    {
        return term.show_cursor();
    }
};

}
