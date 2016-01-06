#include "terminalpp/views/default_draw_context.hpp"

namespace terminalpp { namespace views {

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
default_draw_context::default_draw_context(terminalpp::canvas_view &canvas_view)
  : canvas_view_(canvas_view)
{
}

// ==========================================================================
// GET_CANVAS
// ==========================================================================
terminalpp::canvas_view &default_draw_context::get_canvas()
{
    return canvas_view_;
}

}}