#include "terminalpp/terminal.hpp"
#include "terminalpp/detail/element_difference.hpp"
#include <fmt/format.h>

namespace terminalpp { namespace {

// ==========================================================================
// WRITE_CURSOR_POSITION
// ==========================================================================
void write_cursor_position(
    point const destination,
    behaviour const &beh,
    write_function const &write_fn)
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
            write_fn(to_bytes(fmt::format("{};{}",
                destination.y_ + 1,
                destination.x_ + 1
            )));
        }
    }

    static byte_storage const cursor_position_suffix = {
        ansi::csi::cursor_position
    };

    write_fn(cursor_position_suffix);
}

// ==========================================================================
// WRITE_CURSOR_HORIZONTAL_ABSOLUTE
// ==========================================================================
void write_cursor_horizontal_absolute(
    coordinate_type const x,
    behaviour const &beh,
    write_function const &write_fn)
{
    detail::csi(beh, write_fn);

    if (x != 0)
    {
        write_fn(to_bytes(fmt::format("{}", x + 1)));
    }

    static byte_storage const cursor_horizontal_absolute_suffix = {
        ansi::csi::cursor_horizontal_absolute
    };

    write_fn(cursor_horizontal_absolute_suffix);
}

// ==========================================================================
// WRITE_CURSOR_UP
// ==========================================================================
void write_cursor_up(
    coordinate_type const distance,
    behaviour const &beh,
    write_function const &write_fn)
{
    detail::csi(beh, write_fn);

    if (distance != 1)
    {
        write_fn(to_bytes(fmt::format("{}", distance)));
    }

    static byte_storage const cursor_up_suffix = {
        ansi::csi::cursor_up
    };

    write_fn(cursor_up_suffix);
}

// ==========================================================================
// WRITE_CURSOR_DOWN
// ==========================================================================
void write_cursor_down(
    coordinate_type const distance,
    behaviour const &beh,
    write_function const &write_fn)
{
    detail::csi(beh, write_fn);

    if (distance != 1)
    {
        write_fn(to_bytes(fmt::format("{}", distance)));
    }

    static byte_storage const cursor_down_suffix = {
        ansi::csi::cursor_down
    };

    write_fn(cursor_down_suffix);
}

// ==========================================================================
// MOVE_FROM_KNOWN_POSITION
// ==========================================================================
void move_from_known_position(
    point const destination,
    behaviour const &beh,
    terminal_state &state,
    write_function const &write_fn)
{
    if (*state.cursor_position_ != destination)
    {
        if (state.cursor_position_->y_ == destination.y_)
        {
            write_cursor_horizontal_absolute(destination.x_, beh, write_fn);
        }
        else if (state.cursor_position_->x_ == destination.x_)
        {
            auto const distance = 
                state.cursor_position_->y_ - destination.y_;

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

}

// ==========================================================================
// MOVE_CURSOR::OPERATOR()
// ==========================================================================
void move_cursor::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    write_function const &write_fn) const
{
    if (!state.cursor_position_)
    {
        write_cursor_position(destination_, beh, write_fn);
    }
    else
    {
        move_from_known_position(destination_, beh, state, write_fn);
    }

    state.cursor_position_ = destination_;
}
    
}
