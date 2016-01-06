#ifndef TERMINALPP_VIEW_HPP_
#define TERMINALPP_VIEW_HPP_

#include "terminalpp/rectangle.hpp"
#include <boost/any.hpp>
#include <memory>

namespace terminalpp {

class draw_context;
class event_context;

//* =========================================================================
/// \brief A Concept class that contains an object that knows how to draw
/// itself in a graphics context and can receive and process arbitrary
/// events.  It also knows how large it would prefer to
/// be.
//* =========================================================================
class view
{
public :
    //* =====================================================================
    /// \brief Constructor
    /// Note: uses the "Own If I Must" protocol: r-values passed in will be
    /// copied/moved and owned, whereas l-values passed in will assume that
    /// the object's lifetime is controlled elsewhere and a reference is
    /// taken instead.
    //* =====================================================================
    template <class Model>
    explicit view(Model &&mdl)
      : self_(new model<Model>(std::forward<Model>(mdl)))
    {
    }

    //* =====================================================================
    /// \brief Commands the view to draw a specific region of the component
    /// on to the given context.
    //* =====================================================================
    void draw(draw_context &dc, rectangle const &region)
    {
        self_->draw(dc, region);
    }

    //* =====================================================================
    /// \brief Returns how large the view thinks it should be in ideal
    /// circumstances.
    //* =====================================================================
    extent get_preferred_size() const
    {
        return self_->get_preferred_size();
    }

    //* =====================================================================
    /// \brief Sets the size of the view.
    //* =====================================================================
    void set_size(extent const &size)
    {
        self_->set_size(size);
    }

    //* =====================================================================
    /// \brief Returns the size of the view.
    //* =====================================================================
    extent get_size() const
    {
        return self_->get_size();
    }

    //* =====================================================================
    /// \brief Sends an arbitrary event to the view.
    //* =====================================================================
    boost::any event(event_context &ec, boost::any const &ev)
    {
        return self_->event(ec, ev);
    }

private :
    struct concept
    {
        virtual ~concept(){}
        virtual void draw(draw_context &dc, rectangle const &region) const = 0;
        virtual extent get_preferred_size() const = 0;
        virtual void set_size(extent const &size) = 0;
        virtual extent get_size() const = 0;
        virtual boost::any event(event_context &ec, boost::any const &ev) = 0;
    };

    template <class Model>
    struct model : concept
    {
        model(Model &&mdl)
          : mdl_(std::forward<Model>(mdl))
        {
        }

        void draw(draw_context &dc, rectangle const &region) const override
        {
            mdl_.draw(dc, region);
        }

        extent get_preferred_size() const override
        {
            return mdl_.get_preferred_size();
        }

        void set_size(extent const &size) override
        {
            mdl_.set_size(size);
        }

        extent get_size() const override
        {
            return mdl_.get_size();
        }

        boost::any event(event_context &ec, boost::any const &ev) override
        {
            return mdl_.event(ec, ev);
        }

        Model mdl_;
    };

    std::unique_ptr<concept> self_;
};

}

#endif
