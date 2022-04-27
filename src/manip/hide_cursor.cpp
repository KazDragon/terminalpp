#include "terminalpp/terminal.hpp"
#include "terminalpp/detail/element_difference.hpp"

namespace terminalpp {

// ==========================================================================
// HIDE_CURSOR::OPERATOR()
// ==========================================================================
void hide_cursor::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    write_function const &write_fn) const
{
    if (!state.cursor_visible_ || *state.cursor_visible_)
    {
        detail::dec_pm(beh, write_fn);
        write_fn({
            std::cbegin(ansi::dec_pm::cursor), 
            std::cend(ansi::dec_pm::cursor)});
        write_fn({
            std::cbegin(ansi::dec_pm::reset),
            std::cend(ansi::dec_pm::reset)});
    }

    state.cursor_visible_ = false;
}

}
