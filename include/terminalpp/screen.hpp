#ifndef TERMINALPP_SCREEN_HPP_
#define TERMINALPP_SCREEN_HPP_

#include "terminalpp/canvas.hpp"
#include "terminalpp/terminal.hpp"
#include <string>
#include <vector>

namespace terminalpp {

//* =========================================================================
/// \brief A class that represents a screen for a terminal.
//* =========================================================================
class TERMINALPP_EXPORT screen
{
public :
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    screen(extent size);

    //* =====================================================================
    /// \brief Draws the current screen to the terminal.
    //* =====================================================================
    std::string draw(terminal &term);

    //* =====================================================================
    /// \brief Subscript operator.
    //* =====================================================================
    canvas::column_proxy operator[](u32 index);
    
private :
    canvas front_buffer_;
    canvas back_buffer_;
};

}

#endif
