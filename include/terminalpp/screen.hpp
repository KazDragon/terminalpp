#pragma once

#include "terminalpp/canvas.hpp"
#include "terminalpp/terminal.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief A class that represents a screen for a terminal.
///
/// The screen class implements a double-buffer, whereby each time that a
/// new canvas is drawn to the terminal, it is compared with the previously
/// drawn screen so that only differences are sent.
//* =========================================================================
class TERMINALPP_EXPORT screen
{
public:
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    explicit screen(terminal &term);

    //* =====================================================================
    /// \brief Draws the canvas to the terminal.
    //* =====================================================================
    void draw(canvas const &cvs);

private:
    terminal &terminal_;
    canvas last_frame_{{}};
};

}  // namespace terminalpp
