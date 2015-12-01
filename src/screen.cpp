#include "terminalpp/screen.hpp"
#include "terminalpp/terminal.hpp"

namespace terminalpp {
    
namespace {

// ==========================================================================
// STRING_FROM_CANVAS
// ==========================================================================
string string_from_canvas(canvas const &cvs, point const &pos, s32 width)
{
    auto content = ""_ts;
    
    for (s32 x = pos.x; x < pos.x + width; ++x)
    {
        content += cvs[x][pos.y];
    }
    
    return content;
}
    
// ==========================================================================
// DRAW_ENTIRE_CANVAS
// ==========================================================================
std::string draw_entire_canvas(terminal &term, canvas const &cvs)
{
    std::string result;
    auto const size = cvs.size();
    
    for (s32 row = 0; row < size.height; ++row)
    {
        result += term.move_cursor({0, row});
        result += term.write(string_from_canvas(cvs, {0, row}, size.width));
    }
    
    return result;
}

// ==========================================================================
// DRAW_CANVAS_DIFFERENCES
// ==========================================================================
std::string draw_canvas_differences(
    terminal &term, canvas const &front_canvas, canvas const &back_canvas)
{
    std::string result;
    auto const size = front_canvas.size();
    
    for (s32 row = 0; row < size.height; ++row)
    {
        for (s32 column = 0; column < size.width; ++column)
        {
            auto const &front_element = front_canvas[column][row];
            auto const &back_element = back_canvas[column][row];
            
            if (front_element != back_element)
            {
                result += term.move_cursor({column, row});
                result += term.write(""_ets + front_element);
            }
        }
    }
    
    return result;
}

}

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
                result += term.write(""_ts + cvs[x][y]);
            }
        }
    }
    
    last_frame_ = cvs;

    return result;
}

}
