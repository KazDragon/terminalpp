#include "terminalpp/views/default_view_context.hpp"

namespace terminalpp { namespace views {

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
default_view_context::default_view_context(terminalpp::canvas_view &canvas_view)
  : canvas_view_(canvas_view)
{
}

// ==========================================================================
// GET_CANVAS
// ==========================================================================
terminalpp::canvas_view &default_view_context::get_canvas()
{
    return canvas_view_;
}

}}