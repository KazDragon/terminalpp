#ifndef TERMINALPP_EVENT_CONTEXT_HPP_
#define TERMINALPP_EVENT_CONTEXT_HPP_

#include <memory>
#include <utility>

namespace terminalpp {

//* =========================================================================
/// \brief A Concept class that represents everything necessary for a view
/// to react to an event.
//* =========================================================================
class event_context
{
public :
    template <class Model>
    explicit event_context(Model &&mdl)
      : self_(new model<Model>(std::forward<Model>(mdl)))
    {
    }

private :
    struct concept
    {
        virtual ~concept(){}
    };

    template <class Model>
    struct model : concept
    {
        model(Model &&mdl)
          : mdl_(std::forward<Model>(mdl))
        {
        }

        Model mdl_;
    };

    std::unique_ptr<concept> self_;
};

}

#endif
