#pragma once

#include "terminalpp/algorithm/for_each_in_region.hpp"
#include "terminalpp/canvas.hpp"
#include "terminalpp/terminal.hpp"
#include <string>

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
    screen();

    //* =====================================================================
    /// \brief Draws the current screen to the terminal.
    //* =====================================================================
    template <class WriteContinuation>
    void draw(
        terminal &term, 
        canvas const &cvs,
        WriteContinuation &&wc)
    {
        if (cvs.size() != last_frame_.size())
        {
            last_frame_ = canvas(cvs.size());
            term.write(wc) << erase_display();
        }

        for_each_in_region(
            cvs, {{}, cvs.size()},
            [this, &term, &wc](
                element const &elem, coordinate_type x, coordinate_type y)
            {
                if (last_frame_[x][y] != elem)
                {
                    term.write(wc)
                        << move_cursor({x, y})
                        << elem;
                }
            });

        last_frame_ = cvs;
    }

private :
    canvas last_frame_;
};

}
