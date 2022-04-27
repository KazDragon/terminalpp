#include "terminalpp/terminal.hpp"
#include "terminalpp/detail/element_difference.hpp"

namespace terminalpp {

// ==========================================================================
// RESTORE_CURSOR_POSITION::OPERATOR()
// ==========================================================================
void restore_cursor_position::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    write_function const &write_fn) const
{
    detail::csi(beh, write_fn);

    static byte_storage const restore_cursor_suffix = {
        ansi::csi::restore_cursor_position
    };

    write_fn(restore_cursor_suffix);

    state.cursor_position_ = state.saved_cursor_position_;
}

}
