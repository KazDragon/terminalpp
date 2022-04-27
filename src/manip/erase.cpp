#include "terminalpp/terminal.hpp"
#include "terminalpp/detail/element_difference.hpp"

namespace terminalpp {

// ==========================================================================
// ERASE_DISPLAY::OPERATOR()
// ==========================================================================
void erase_display::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    write_function const &write_fn) const
{
    detail::change_to_default_attribute(state.last_element_, beh, write_fn);
    detail::csi(beh, write_fn);

    static byte_storage const erase_all_suffix = {  
        ansi::csi::erase_in_display_all,
        ansi::csi::erase_in_display,
    };

    write_fn(erase_all_suffix);
}

// ==========================================================================
// ERASE_DISPLAY_ABOVE::OPERATOR()
// ==========================================================================
void erase_display_above::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    write_function const &write_fn) const
{
    detail::change_to_default_attribute(state.last_element_, beh, write_fn);
    detail::csi(beh, write_fn);

    static byte_storage const erase_above_suffix = {  
        ansi::csi::erase_in_display_above,
        ansi::csi::erase_in_display,
    };

    write_fn(erase_above_suffix);
}

// ==========================================================================
// ERASE_DISPLAY_BELOW::OPERATOR()
// ==========================================================================
void erase_display_below::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    write_function const &write_fn) const
{
    detail::change_to_default_attribute(state.last_element_, beh, write_fn);
    detail::csi(beh, write_fn);

    static byte_storage const erase_below_suffix = {  
        // The constant for erase below is 0, which can be elided
        ansi::csi::erase_in_display,
    };

    write_fn(erase_below_suffix);
}

// ==========================================================================
// ERASE_LINE::OPERATOR()
// ==========================================================================
void erase_line::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    write_function const &write_fn) const
{
    detail::change_to_default_attribute(state.last_element_, beh, write_fn);
    detail::csi(beh, write_fn);

    static byte_storage const erase_line_suffix = {  
        ansi::csi::erase_in_line_all,
        ansi::csi::erase_in_line,
    };

    write_fn(erase_line_suffix);
}

// ==========================================================================
// ERASE_LINE_LEFT::OPERATOR()
// ==========================================================================
void erase_line_left::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    write_function const &write_fn) const
{
    detail::change_to_default_attribute(state.last_element_, beh, write_fn);
    detail::csi(beh, write_fn);

    static byte_storage const erase_line_left_suffix = {  
        ansi::csi::erase_in_line_left,
        ansi::csi::erase_in_line,
    };

    write_fn(erase_line_left_suffix);
}

// ==========================================================================
// ERASE_LINE_RIGHT::OPERATOR()
// ==========================================================================
void erase_line_right::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    write_function const &write_fn) const
{
    detail::change_to_default_attribute(state.last_element_, beh, write_fn);
    detail::csi(beh, write_fn);

    static byte_storage const erase_line_right_suffix = {  
        // The code for erase right is 0, which can be elided.
        ansi::csi::erase_in_line,
    };

    write_fn(erase_line_right_suffix);
}

}
