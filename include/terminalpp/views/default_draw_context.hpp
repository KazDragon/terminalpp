#ifndef TERMINALPP_VIEWS_DEFAULT_DRAW_CONTEXT_HPP_
#define TERMINALPP_VIEWS_DEFAULT_DRAW_CONTEXT_HPP_

#include "terminalpp/detail/export.hpp"

namespace terminalpp {

class canvas_view;

namespace views {

//* =========================================================================
/// \brief A default implementation of the draw_context concept.
//* =========================================================================
class TERMINALPP_EXPORT default_draw_context
{
public :
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    default_draw_context(terminalpp::canvas_view &canvas_view);

    //* =====================================================================
    /// \brief Returns this context's canvas view.
    //* =====================================================================
    terminalpp::canvas_view &get_canvas();

private :
    terminalpp::canvas_view &canvas_view_;
};

}}

#endif
