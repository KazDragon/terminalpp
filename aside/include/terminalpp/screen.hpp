#pragma once

#include "terminalpp/canvas.hpp"
#include <string>

namespace terminalpp {

class terminal;

//* =========================================================================
/// \brief A class that represents a screen for a terminal.
//* =========================================================================
class TERMINALPP_EXPORT screen
{
public :
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    screen();

    //* =====================================================================
    /// \brief Draws the current screen to the terminal.
    //* =====================================================================
    std::string draw(terminal &term, canvas const &cvs);

private :
    canvas last_frame_;
};

}
