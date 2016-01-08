#include "terminalpp/screen.hpp"
#include "terminalpp/terminal.hpp"

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
std::string screen::draw(terminal& term, canvas const &cvs)
{
    auto result = std::string();

    if (cvs.size() != last_frame_.size())
    {
        last_frame_ = canvas(cvs.size());
        result += term.erase_in_display(terminal::erase_display::all);
    }
    
    for (s32 y = 0; y < cvs.size().height; ++y)
    {
        for (s32 x = 0; x < cvs.size().width; ++x)
        {
            if (last_frame_[x][y] != cvs[x][y])
            {
                result += term.move_cursor({x, y});
                result += term.write(cvs[x][y]);
            }
        }
    }
    
    last_frame_ = cvs;

    return result;
}

}
