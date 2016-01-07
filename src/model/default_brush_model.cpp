#include "terminalpp/model/default_brush_model.hpp"
#include <boost/signals2.hpp>

namespace terminalpp { namespace model {

struct default_brush_model::impl
{
    boost::signals2::signal<void ()> on_model_changed;

    terminalpp::element fill_;
};

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
default_brush_model::default_brush_model()
  : pimpl_(std::make_shared<impl>())
{
}

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
default_brush_model::default_brush_model(terminalpp::element const &fill)
  : pimpl_(std::make_shared<impl>())
{
    pimpl_->fill_ = fill;
}

// ==========================================================================
// SET_FILL
// ==========================================================================
void default_brush_model::set_fill(terminalpp::element const &fill)
{
    pimpl_->fill_ = fill;
    pimpl_->on_model_changed();
}

// ==========================================================================
// GET_FILL
// ==========================================================================
terminalpp::element default_brush_model::get_fill() const
{
    return pimpl_->fill_;
}

// ==========================================================================
// ON_MODEL_CHANGED
// ==========================================================================
void default_brush_model::on_model_changed(
    std::function<void ()> const &callable)
{
    pimpl_->on_model_changed.connect(callable);
}

}}
