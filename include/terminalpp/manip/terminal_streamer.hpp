#pragma once
#include "terminalpp/core.hpp"
#include <string>

namespace terminalpp {

class terminal;
class string;

//* =========================================================================
/// \brief A class that encapsulates commands being streamed to a terminal.
//* =========================================================================
class terminal_streamer
{
public :
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    terminal_streamer(terminal &term)
      : terminal_(term)
    {
    }

    //* =====================================================================
    /// \brief Converts the result of the streaming operation to a string.
    //* =====================================================================
    operator std::string() const
    {
        return result_;
    }

    //* =====================================================================
    /// \brief Streams an operation into the streamer.
    //* =====================================================================
    template <class Op>
    terminal_streamer &operator<<(Op &&op)
    {
        result_ += op(terminal_);
        return *this;
    }

    //* =====================================================================
    /// \brief Streams a string into the streamer.
    //* =====================================================================
    TERMINALPP_EXPORT
    terminal_streamer &operator<<(string const &text);

    //* =====================================================================
    /// \brief Streams a string into the streamer.
    //* =====================================================================
    TERMINALPP_EXPORT
    terminal_streamer &operator<<(string &&text);

private :
    terminal &terminal_;
    std::string result_;
};

}
