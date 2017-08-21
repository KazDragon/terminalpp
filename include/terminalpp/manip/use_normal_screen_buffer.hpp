#pragma once
#include "terminalpp/terminal.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief A structure that encapsulates a use normal screen buffer operation
//* =========================================================================
struct use_normal_screen_buffer
{
    //* =====================================================================
    /// \brief Uses the normal screen buffer in the terminal.
    //* =====================================================================
    std::string operator()(terminal &term)
    {
        return term.use_normal_screen_buffer();
    }
};

}
