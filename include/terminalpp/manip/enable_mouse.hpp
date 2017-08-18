#pragma once
#include "terminalpp/terminal.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief A structure that encapsulates mouse enable operation
//* =========================================================================
struct enable_mouse
{
    //* =====================================================================
    /// \brief Enables the mouse in the terminal.
    //* =====================================================================
    std::string operator()(terminal &term)
    {
        return term.enable_mouse();
    }
};

}