#pragma once
#include "terminalpp/point.hpp"
#include "terminalpp/terminal.hpp"
#include <string>

namespace terminalpp {

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

//* =========================================================================
/// \brief Streams an operation into a terminal, yielding a terminal_streamer
/// that allows further streaming operations in the expression.
//* =========================================================================
template <class Op>
terminal_streamer operator<<(terminal &term, Op &&op)
{
    terminal_streamer streamer(term);
    streamer << std::forward<Op>(op);
    return streamer;
}

//* =========================================================================
/// \brief Encapsulates writing a string to a terminal.
//* =========================================================================
struct write_string
{
    write_string(string const &text)
      : text_(text)
    {
    }

    std::string operator()(terminal &term) const
    {
        return term.write(text_);
    }

    string const &text_;
};

//* =========================================================================
/// \brief A structure that encapsulates a cursor move operation
//* =========================================================================
struct move_cursor
{
    constexpr move_cursor(terminalpp::point position)
      : position_(position)
    {
    }

    std::string operator()(terminal &term)
    {
        return term.move_cursor(position_);
    }

    terminalpp::point position_;
};

//* =========================================================================
/// \brief A structure that encapsulates a mouse enable operation
//* =========================================================================
struct enable_mouse
{
    std::string operator()(terminal &term)
    {
        return term.enable_mouse();
    }
};

//* =========================================================================
/// \brief A structure that encapsulates a mouse disable operation
//* =========================================================================
struct disable_mouse
{
    std::string operator()(terminal &term)
    {
        return term.disable_mouse();
    }
};

//* =========================================================================
/// \brief A structure that encapsulates a window title operation
//* =========================================================================
struct set_window_title
{
    set_window_title(std::string title)
      : title_(std::move(title))
    {
    }

    std::string operator()(terminal &term)
    {
        return term.set_window_title(title_);
    }

    std::string title_;
};

}
