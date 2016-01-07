#ifndef TERMINALPP_MODEL_DEFAULT_BRUSH_MODEL_HPP_
#define TERMINALPP_MODEL_DEFAULT_BRUSH_MODEL_HPP_

#include "terminalpp/element.hpp"
#include <functional>
#include <memory>

namespace terminalpp { namespace model {

//* =========================================================================
/// \brief A default implementation of a brush model.
//* =========================================================================
class TERMINALPP_EXPORT default_brush_model
{
public :
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    default_brush_model();

    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    explicit default_brush_model(terminalpp::element const &fill);

    //* =====================================================================
    /// \brief Sets the fill pattern.
    //* =====================================================================
    void set_fill(terminalpp::element const &fill);

    //* =====================================================================
    /// \brief Gets the fill pattern.
    //* =====================================================================
    terminalpp::element get_fill() const;

    //* =====================================================================
    /// \brief Add a callback to be executed when the model changes.
    //* =====================================================================
    void on_model_changed(std::function<void ()> const &callable);

private :
    struct impl;
    std::shared_ptr<impl> pimpl_;
};

}}

#endif
