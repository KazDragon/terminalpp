#include "terminalpp/model/default_brush_model.hpp"

namespace terminalpp { namespace model {

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
default_brush_model::default_brush_model()
{
}

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
default_brush_model::default_brush_model(terminalpp::element const &fill)
  : fill_(fill)
{
}

// ==========================================================================
// SET_FILL
// ==========================================================================
void default_brush_model::set_fill(terminalpp::element const &fill)
{
    fill_ = fill;
}

// ==========================================================================
// GET_FILL
// ==========================================================================
terminalpp::element default_brush_model::get_fill() const
{
    return fill_;
}

}}
