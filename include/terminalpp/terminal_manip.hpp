#pragma once
#include "terminalpp/point.hpp"
#include "terminalpp/terminal.hpp"
#include <string>

namespace terminalpp {

class string;

//* =========================================================================
//* =========================================================================
class terminal_streamer
{
public :
    terminal_streamer(terminal &term)
      : terminal_(term)
    {
    }

    operator std::string() const
    {
        return result_;
    }

    template <class Op>
    terminal_streamer &operator<<(Op &&op)
    {
        result_ += op(terminal_);
        return *this;
    }

    terminal_streamer &operator<<(string const &text);
    terminal_streamer &operator<<(string &&text);

private :
    terminal &terminal_;
    std::string result_;
};

//* =========================================================================
///
//* =========================================================================
template <class Op>
terminal_streamer operator<<(terminal &term, Op &&op)
{
    terminal_streamer streamer(term);
    streamer << std::forward<Op>(op);
    return streamer;
}

//* =========================================================================
///
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
//* =========================================================================
terminal_streamer &terminal_streamer::operator<<(string const &text)
{
    return *this << write_string(text);
}

//* =========================================================================
//* =========================================================================
terminal_streamer &terminal_streamer::operator<<(string &&text)
{
    return *this << write_string(std::move(text));
}

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

}
