#include "terminalpp/views/brush_view.hpp"
#include "terminalpp/model/default_brush_model.hpp"
#include "terminalpp/canvas_view.hpp"
#include "terminalpp/draw_context.hpp"

namespace terminalpp { namespace views {

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
brush_view::brush_view()
  : model_(terminalpp::model::default_brush_model())
{
}

// ==========================================================================
// DRAW
// ==========================================================================
void brush_view::draw(
    terminalpp::draw_context &dc,
    terminalpp::rectangle const &region) const
{
    auto &canvas = dc.get_canvas();
    auto const &fill = model_.get_fill();

    for (auto row = region.origin.y;
         row < (region.origin.y + region.size.height);
         ++row)
    {
        for (auto col = region.origin.x;
             col < (region.origin.x + region.size.width);
             ++col)
        {
            canvas[col][row] = fill;
        }
    }
}

// ==========================================================================
// GET_PREFERRED_SIZE
// ==========================================================================
terminalpp::extent brush_view::get_preferred_size() const
{
    return size_;
}

// ==========================================================================
// SET_SIZE
// ==========================================================================
void brush_view::set_size(terminalpp::extent const &size)
{
    size_ = size;
}

// ==========================================================================
// GET_SIZE
// ==========================================================================
terminalpp::extent brush_view::get_size() const
{
    return size_;
}

// ==========================================================================
// EVENT
// ==========================================================================
boost::any brush_view::event(
    terminalpp::event_context &ec, boost::any const &ev)
{
    return {};
}

}}
