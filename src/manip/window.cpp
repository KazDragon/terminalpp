#include "terminalpp/ansi/dec_private_mode.hpp"
#include "terminalpp/ansi/osc.hpp"
#include "terminalpp/detail/element_difference.hpp"
#include "terminalpp/terminal.hpp"

namespace terminalpp {

// ==========================================================================
// SET_WINDOW_TITLE::OPERATOR()
// ==========================================================================
void set_window_title::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    terminal::write_function const &write_fn) const
{
    static byte_storage const set_window_title_prefix = {
        ansi::osc::set_window_title,
        ansi::ps,
    };

    if (beh.supports_window_title_bel)
    {
        detail::osc(beh, write_fn);

        write_fn(set_window_title_prefix);
        write_fn(
            {reinterpret_cast<byte const *>(title_.data()), title_.size()});

        static byte_storage const set_window_title_bel_suffix = {
            detail::ascii::bel};

        write_fn(set_window_title_bel_suffix);
    }
    else if (beh.supports_window_title_st)
    {
        detail::osc(beh, write_fn);

        write_fn(set_window_title_prefix);
        write_fn(
            {reinterpret_cast<byte const *>(title_.data()), title_.size()});

        detail::st(beh, write_fn);
    }
}

// ==========================================================================
// USE_NORMAL_SCREEN_BUFFER::OPERATOR()
// ==========================================================================
void use_normal_screen_buffer::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    terminal::write_function const &write_fn) const
{
    detail::dec_pm(beh, write_fn);

    write_fn(
        {std::cbegin(ansi::dec_pm::use_alternate_screen_buffer),
         std::cend(ansi::dec_pm::use_alternate_screen_buffer)});

    write_fn(
        {std::cbegin(ansi::dec_pm::reset), std::cend(ansi::dec_pm::reset)});
}

// ==========================================================================
// USE_ALTERNATE_SCREEN_BUFFER::OPERATOR()
// ==========================================================================
void use_alternate_screen_buffer::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    terminal::write_function const &write_fn) const
{
    detail::dec_pm(beh, write_fn);

    write_fn(
        {std::cbegin(ansi::dec_pm::use_alternate_screen_buffer),
         std::cend(ansi::dec_pm::use_alternate_screen_buffer)});

    write_fn({std::cbegin(ansi::dec_pm::set), std::cend(ansi::dec_pm::set)});
}

}  // namespace terminalpp
