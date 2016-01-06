#ifndef TERMINALPP_DRAW_CONTEXT_HPP_
#define TERMINALPP_DRAW_CONTEXT_HPP_

#include <memory>
#include <utility>

namespace terminalpp {

class canvas_view;

//* =========================================================================
/// \brief A Concept class that represents everything necessary for a view
/// to draw itself.
//* =========================================================================
class draw_context
{
public :
    template <class Model>
    explicit draw_context(Model &&mdl)
      : self_(new model<Model>(std::forward<Model>(mdl)))
    {
    }

    //* =====================================================================
    /// \brief Returns the context's canvas view onto which a view should
    /// draw itself.
    //* =====================================================================
    canvas_view &get_canvas()
    {
        return self_->get_canvas();
    }

private :
    struct concept
    {
        virtual ~concept(){}
        virtual canvas_view &get_canvas() = 0;
    };

    template <class Model>
    struct model : concept
    {
        model(Model &&mdl)
          : mdl_(std::forward<Model>(mdl))
        {
        }

        canvas_view &get_canvas() override
        {
            return mdl_.get_canvas();
        }

        Model mdl_;
    };

    std::unique_ptr<concept> self_;
};

}

#endif
