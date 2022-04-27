#include "terminalpp/screen.hpp"
#include "terminalpp/algorithm/for_each_in_region.hpp"

namespace terminalpp { 

void screen::draw(terminal &term, canvas const &cvs)
{
    if (cvs.size() != last_frame_.size())
    {
        last_frame_ = canvas(cvs.size());
        term << erase_display();
    }

    for_each_in_region(
        cvs, {{}, cvs.size()},
        [this, &term, &wc](
            element const &elem, coordinate_type x, coordinate_type y)
        {
            if (last_frame_[x][y] != elem)
            {
                term << move_cursor({x, y})
                     << elem;
            }
        });

    last_frame_ = cvs;
}

}
