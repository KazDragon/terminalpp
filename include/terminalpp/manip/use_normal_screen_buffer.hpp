#pragma once
#include "terminalpp/terminal.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief A structure that encapsulates mouse enable operation
//* =========================================================================
struct use_normal_screen_buffer
{
    //* =====================================================================
    /// \brief Enables the mouse in the terminal.
    //* =====================================================================
    std::string operator()(terminal &term)
    {
        return term.use_normal_screen_buffer();
    }
};

}
