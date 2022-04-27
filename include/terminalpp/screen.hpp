#pragma once

#include "terminalpp/canvas.hpp"
#include "terminalpp/terminal.hpp"
#include <string>

namespace terminalpp {

//* =========================================================================
/// \brief A class that represents a screen for a terminal.
///
/// The screen class implements a double-buffer, whereby each time that a
/// new canvas is drawn to the terminal, it is compared with the previously
/// drawn screen so that only differences are sent.
//* =========================================================================
class screen
{
public :
    //* =====================================================================
    /// \brief Draws the canvas to the terminal.
    //* =====================================================================
    void draw(terminal &term, canvas const &cvs);

private :
    canvas last_frame_{{}};
};

}
