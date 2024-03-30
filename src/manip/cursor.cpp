#include "terminalpp/detail/element_difference.hpp"
#include "terminalpp/terminal.hpp"

#include <fmt/format.h>

namespace terminalpp {
namespace {

// ==========================================================================
// WRITE_CURSOR_POSITION
// ==========================================================================
void write_cursor_position(
    point const destination,
    behaviour const &beh,
    terminal::write_function const &write_fn)
{
    detail::csi(beh, write_fn);

    if (destination.x_ != 0 || destination.y_ != 0)
    {
        if (destination.x_ == 0)
        {
            write_fn(to_bytes(fmt::format("{}", destination.y_ + 1)));
        }
        else
        {
            write_fn(to_bytes(
                fmt::format("{};{}", destination.y_ + 1, destination.x_ + 1)));
        }
    }

    static byte_storage const cursor_position_suffix = {
        ansi::csi::cursor_position};

    write_fn(cursor_position_suffix);
}

// ==========================================================================
// WRITE_CURSOR_HORIZONTAL_ABSOLUTE
// ==========================================================================
void write_cursor_horizontal_absolute(
    coordinate_type const x,
    behaviour const &beh,
    terminal::write_function const &write_fn)
{
    detail::csi(beh, write_fn);

    if (x != 0)
    {
        write_fn(to_bytes(fmt::format("{}", x + 1)));
    }

    static byte_storage const cursor_horizontal_absolute_suffix = {
        ansi::csi::cursor_horizontal_absolute};

    write_fn(cursor_horizontal_absolute_suffix);
}

// ==========================================================================
// WRITE_CURSOR_UP
// ==========================================================================
void write_cursor_up(
    coordinate_type const distance,
    behaviour const &beh,
    terminal::write_function const &write_fn)
{
    detail::csi(beh, write_fn);

    if (distance != 1)
    {
        write_fn(to_bytes(fmt::format("{}", distance)));
    }

    static byte_storage const cursor_up_suffix = {ansi::csi::cursor_up};

    write_fn(cursor_up_suffix);
}

// ==========================================================================
// WRITE_CURSOR_DOWN
// ==========================================================================
void write_cursor_down(
    coordinate_type const distance,
    behaviour const &beh,
    terminal::write_function const &write_fn)
{
    detail::csi(beh, write_fn);

    if (distance != 1)
    {
        write_fn(to_bytes(fmt::format("{}", distance)));
    }

    static byte_storage const cursor_down_suffix = {ansi::csi::cursor_down};

    write_fn(cursor_down_suffix);
}

// ==========================================================================
// MOVE_FROM_KNOWN_POSITION
// ==========================================================================
void move_from_known_position(
    point const destination,
    behaviour const &beh,
    point const &cursor_position,
    terminal::write_function const &write_fn)
{
    if (cursor_position != destination)
    {
        if (cursor_position.y_ == destination.y_)
        {
            write_cursor_horizontal_absolute(destination.x_, beh, write_fn);
        }
        else if (cursor_position.x_ == destination.x_)
        {
            auto const distance = cursor_position.y_ - destination.y_;

            if (distance > 0)
            {
                write_cursor_up(distance, beh, write_fn);
            }
            else
            {
                write_cursor_down(-distance, beh, write_fn);
            }
        }
        else
        {
            write_cursor_position(destination, beh, write_fn);
        }
    }
}

}  // namespace

// ==========================================================================
// MOVE_CURSOR::OPERATOR()
// ==========================================================================
void move_cursor::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    terminal::write_function const &write_fn) const
{
    if (!state.cursor_position_)
    {
        write_cursor_position(destination_, beh, write_fn);
    }
    else
    {
        move_from_known_position(
            destination_, beh, *state.cursor_position_, write_fn);
    }

    state.cursor_position_ = destination_;
}

// ==========================================================================
// HIDE_CURSOR::OPERATOR()
// ==========================================================================
void hide_cursor::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    terminal::write_function const &write_fn) const
{
    if (!state.cursor_visible_ || *state.cursor_visible_)
    {
        detail::dec_pm(beh, write_fn);
        write_fn(
            {std::cbegin(ansi::dec_pm::cursor),
             std::cend(ansi::dec_pm::cursor)});
        write_fn(
            {std::cbegin(ansi::dec_pm::reset), std::cend(ansi::dec_pm::reset)});
    }

    state.cursor_visible_ = false;
}

// ==========================================================================
// SHOW_CURSOR::OPERATOR()
// ==========================================================================
void show_cursor::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    terminal::write_function const &write_fn) const
{
    if (!state.cursor_visible_ || !*state.cursor_visible_)
    {
        detail::dec_pm(beh, write_fn);
        write_fn(
            {std::cbegin(ansi::dec_pm::cursor),
             std::cend(ansi::dec_pm::cursor)});
        write_fn(
            {std::cbegin(ansi::dec_pm::set), std::cend(ansi::dec_pm::set)});
    }

    state.cursor_visible_ = true;
}

// ==========================================================================
// SAVE_CURSOR_POSITION::OPERATOR()
// ==========================================================================
void save_cursor_position::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    terminal::write_function const &write_fn) const
{
    detail::csi(beh, write_fn);

    static byte_storage const save_cursor_suffix = {
        ansi::csi::save_cursor_position};

    write_fn(save_cursor_suffix);

    state.saved_cursor_position_ = state.cursor_position_;
}

// ==========================================================================
// RESTORE_CURSOR_POSITION::OPERATOR()
// ==========================================================================
void restore_cursor_position::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    terminal::write_function const &write_fn) const
{
    detail::csi(beh, write_fn);

    static byte_storage const restore_cursor_suffix = {
        ansi::csi::restore_cursor_position};

    write_fn(restore_cursor_suffix);

    state.cursor_position_ = state.saved_cursor_position_;
}

}  // namespace terminalpp
