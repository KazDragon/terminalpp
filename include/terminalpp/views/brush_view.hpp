#ifndef TERMINALPP_VIEWS_BRUSH_VIEW_HPP_
#define TERMINALPP_VIEWS_BRUSH_VIEW_HPP_

#include "terminalpp/models/brush_model.hpp"
#include "terminalpp/rectangle.hpp"
#include <boost/any.hpp>
#include <utility>

namespace terminalpp {

class draw_context;
class event_context;

namespace views {

//* =========================================================================
/// \brief A Concept that contains an object that is a view of a brush.
/// That is, a view with a solid fill pattern.
//* =========================================================================
class TERMINALPP_EXPORT brush_view
{
public :
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    brush_view();

    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    template <class Model>
    brush_view(Model &&model)
      : model_(std::forward<Model>(model))
    {
    }

    //* =====================================================================
    /// \brief Draws the view.
    //* =====================================================================
    void draw(
        terminalpp::draw_context &dc,
        terminalpp::rectangle const &region) const;

    //* =====================================================================
    /// \brief Returns the preferred size of the view.  This is always the
    /// current size of the view.
    //* =====================================================================
    terminalpp::extent get_preferred_size() const;

    //* =====================================================================
    /// \brief Sets the size of the view.
    //* =====================================================================
    void set_size(terminalpp::extent const &size);

    //* =====================================================================
    /// \brief Gets the size of the view.
    //* =====================================================================
    terminalpp::extent get_size() const;

    //* =====================================================================
    /// \brief Sends an event to the view.  This always goes unhandled.
    //* =====================================================================
    boost::any event(terminalpp::event_context &ec, boost::any const &ev);

private :
    terminalpp::extent size_;
    terminalpp::models::brush_model model_;
};

}}

#endif
