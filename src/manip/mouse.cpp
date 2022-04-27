#include "terminalpp/terminal.hpp"
#include "terminalpp/detail/element_difference.hpp"

namespace terminalpp {

// ==========================================================================
// ENABLE_MOUSE::OPERATOR()
// ==========================================================================
void enable_mouse::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    terminal::write_function const &write_fn) const
{
    if (beh.supports_basic_mouse_tracking)
    {
        detail::dec_pm(beh, write_fn);
        write_fn({
            std::cbegin(ansi::dec_pm::basic_mouse_tracking),
            std::cend(ansi::dec_pm::basic_mouse_tracking)});
        write_fn({
            std::cbegin(ansi::dec_pm::set),
            std::cend(ansi::dec_pm::set)});
    }
    else if (beh.supports_all_mouse_motion_tracking)
    {
        detail::dec_pm(beh, write_fn);
        write_fn({
            std::cbegin(ansi::dec_pm::all_motion_mouse_tracking),
            std::cend(ansi::dec_pm::all_motion_mouse_tracking)});
        write_fn({
            std::cbegin(ansi::dec_pm::set),
            std::cend(ansi::dec_pm::set)});
    }
}

// ==========================================================================
// DISABLE_MOUSE::OPERATOR()
// ==========================================================================
void disable_mouse::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    terminal::write_function const &write_fn) const
{
    if (beh.supports_basic_mouse_tracking)
    {
        detail::dec_pm(beh, write_fn);
        write_fn({
            std::cbegin(ansi::dec_pm::basic_mouse_tracking),
            std::cend(ansi::dec_pm::basic_mouse_tracking)});
        write_fn({
            std::cbegin(ansi::dec_pm::reset),
            std::cend(ansi::dec_pm::reset)});
    }
    else if (beh.supports_all_mouse_motion_tracking)
    {
        detail::dec_pm(beh, write_fn);
        write_fn({
            std::cbegin(ansi::dec_pm::all_motion_mouse_tracking),
            std::cend(ansi::dec_pm::all_motion_mouse_tracking)});
        write_fn({
            std::cbegin(ansi::dec_pm::reset),
            std::cend(ansi::dec_pm::reset)});
    }
}

}
