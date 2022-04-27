#include "terminalpp/terminal.hpp"
#include "terminalpp/detail/element_difference.hpp"

namespace terminalpp {

// ==========================================================================
// SAVE_CURSOR_POSITION::OPERATOR()
// ==========================================================================
void save_cursor_position::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    write_function const &write_fn) const
{
    detail::csi(beh, write_fn);

    static byte_storage const save_cursor_suffix = {
        ansi::csi::save_cursor_position
    };

    write_fn(save_cursor_suffix);

    state.saved_cursor_position_ = state.cursor_position_;
}

}
