#pragma once
#include "terminalpp/terminal.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief A structure that encapsulates mouse disable operation
//* =========================================================================
struct disable_mouse
{
    //* =====================================================================
    /// \brief Disables the mouse in the terminal.
    //* =====================================================================
    std::string operator()(terminal &term)
    {
        return term.disable_mouse();
    }
};

}
