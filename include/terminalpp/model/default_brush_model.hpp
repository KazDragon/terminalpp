#ifndef TERMINALPP_MODEL_DEFAULT_BRUSH_MODEL_HPP_
#define TERMINALPP_MODEL_DEFAULT_BRUSH_MODEL_HPP_

#include "terminalpp/element.hpp"

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

private :
    terminalpp::element fill_;
};

}}

#endif
