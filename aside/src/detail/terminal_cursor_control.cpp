#include "terminalpp/behaviour.hpp"
#include "terminalpp/ansi/protocol.hpp"
#include "terminalpp/detail/terminal_cursor_control.hpp"
#include "terminalpp/detail/terminal_control.hpp"
#include "terminalpp/point.hpp"

namespace terminalpp { namespace detail {

// ==========================================================================
// CURSOR_UP
// ==========================================================================
byte_storage cursor_up(
    coordinate_type     y,
    control_mode const &mode)
{
    byte_storage result = csi(mode);

    // If y is 1, then we can skip the amount indicator.  Note: Pretty much
    // anything that supports CUA supports the default, so this isn't checked
    // in the behaviour.
    if (y != 1)
    {
        result += to_bytes(std::to_string(y));
    }

    result += terminalpp::ansi::csi::CURSOR_UP;

    return result;
}

// ==========================================================================
// CURSOR_UP
// ==========================================================================
byte_storage cursor_down(
    coordinate_type     y,
    control_mode const &mode)
{
    byte_storage result = csi(mode);

    // If y is 1, then we can skip the amount indicator.  Note: Pretty much
    // anything that supports CUB supports the default, so this isn't checked
    // in the behaviour.
    if (y != 1)
    {
        result += to_bytes(std::to_string(y));
    }

    result += terminalpp::ansi::csi::CURSOR_DOWN;

    return result;
}

// ==========================================================================
// CURSOR_FORWARD
// ==========================================================================
byte_storage cursor_forward(
    coordinate_type     x,
    control_mode const &mode)
{
    byte_storage result = csi(mode);

    // If x is 1, then we can skip the amount indicator.  Note: Pretty much
    // anything that supports CUF supports the default, so this isn't checked
    // in the behaviour.
    if (x != 1)
    {
        result += to_bytes(std::to_string(x));
    }

    result += terminalpp::ansi::csi::CURSOR_FORWARD;

    return result;
}

// ==========================================================================
// CURSOR_BACKWARD
// ==========================================================================
byte_storage cursor_backward(
    coordinate_type     x,
    control_mode const &mode)
{
    byte_storage result = csi(mode);

    // If x is 1, then we can skip the amount indicator.  Note: Pretty much
    // anything that supports CUB supports the default, so this isn't checked
    // in the behaviour.
    if (x != 1)
    {
        result += to_bytes(std::to_string(x));
    }

    result += terminalpp::ansi::csi::CURSOR_BACKWARD;

    return result;
}

// ==========================================================================
// CURSOR_HORIZONTAL_ABSOLUTE
// ==========================================================================
byte_storage cursor_horizontal_absolute(
    coordinate_type              x,
    terminalpp::behaviour const &behaviour,
    control_mode          const &mode)
{
    byte_storage result;

    result += csi(mode);

    // If x is 1, and our terminal supports CHA with a default argument, then
    // we can skip the character the column indicator.  Otherwise, we have to
    // include it.
    if (x != 1 || !behaviour.supports_cha_default)
    {
        result += to_bytes(std::to_string(x));
    }

    result += terminalpp::ansi::csi::CURSOR_HORIZONTAL_ABSOLUTE;

    return result;
}

// ==========================================================================
// CURSOR_POSITION
// ==========================================================================
byte_storage cursor_position(
    point                 const &pt,
    terminalpp::behaviour const &/*behaviour*/,
    control_mode          const &mode)
{
    auto result = csi(mode);
    if (pt.x != 1 || pt.y != 1)
    {
        result += to_bytes(std::to_string(pt.y))
                + terminalpp::ansi::PS
                + to_bytes(std::to_string(pt.x));
    }
    return result + terminalpp::ansi::csi::CURSOR_POSITION;
}

// ==========================================================================
// LINE_POSITION_ABSOLUTE
// ==========================================================================
byte_storage line_position_absolute(
    coordinate_type              x,
    terminalpp::behaviour const &behaviour,
    control_mode          const &mode)
{
    byte_storage result;

    result += csi(mode);

    // If x is 1, and our terminal supports VPA with a default argument, then
    // we can skip the character the column indicator.  Otherwise, we have to
    // include it.
    if (x != 1 || !behaviour.supports_vpa_default)
    {
        result += to_bytes(std::to_string(x));
    }

    result += terminalpp::ansi::csi::LINE_POSITION_ABSOLUTE;

    return result;
}

}}
