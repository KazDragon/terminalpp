#pragma once
#include "terminalpp/terminal.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief A structure that encapsulates a use alternate screen buffer
/// operation.
//* =========================================================================
struct use_alternate_screen_buffer
{
    //* =====================================================================
    /// \brief Uses the alternate screen buffer in the terminal.
    //* =====================================================================
    std::string operator()(terminal &term)
    {
        return term.use_alternate_screen_buffer();
    }
};

}
