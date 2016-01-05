#ifndef TERMINALPP_VIEWS_BRUSH_VIEW_HPP_
#define TERMINALPP_VIEWS_BRUSH_VIEW_HPP_

#include "terminalpp/model/brush_model.hpp"
#include "terminalpp/rectangle.hpp"
#include <boost/any.hpp>
#include <utility>

namespace terminalpp {

class view_context;

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
        terminalpp::view_context &vc,
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
    boost::any event(terminalpp::view_context &vc, boost::any const &ev);

private :
    terminalpp::extent size_;
    terminalpp::model::brush_model model_;
};

}}

#endif
