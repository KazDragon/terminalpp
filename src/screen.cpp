#include "terminalpp/screen.hpp"
#include "terminalpp/algorithm/for_each_in_region.hpp"

namespace terminalpp { 

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
screen::screen(terminal& term)
  : terminal_(term)
{
}

// ==========================================================================
// DRAW
// ==========================================================================
void screen::draw(canvas const &cvs)
{
    if (cvs.size() != last_frame_.size())
    {
        last_frame_ = canvas(cvs.size());
        terminal_ << erase_display();
    }

    for_each_in_region(
        cvs, {{}, cvs.size()},
        [this](
            element const &elem, coordinate_type x, coordinate_type y)
        {
            if (last_frame_[x][y] != elem)
            {
                terminal_ << move_cursor({x, y})
                          << elem;
            }
        });

    last_frame_ = cvs;
}

}
