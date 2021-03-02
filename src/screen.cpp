#include "terminalpp/screen.hpp"
#include "terminalpp/terminal.hpp"
#include "terminalpp/algorithm/for_each_in_region.hpp"

namespace terminalpp {

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
screen::screen()
  : last_frame_({})
{
}

// ==========================================================================
// DRAW
// ==========================================================================
/*
std::string screen::draw(terminal& term, canvas const &cvs)
{
    auto result = std::string();

    if (cvs.size() != last_frame_.size())
    {
        last_frame_ = canvas(cvs.size());
        result += term.erase_in_display(terminal::erase_display::all);
    }

    for_each_in_region(
        cvs, {{}, cvs.size()},
        [this, &result, &term](
            element const &elem, coordinate_type x, coordinate_type y)
        {
            if (last_frame_[x][y] != elem)
            {
                result += term.move_cursor({x, y});
                result += term.write(elem);
            }
        });
   

    last_frame_ = cvs;

    return result;
}
*/

}
