#include "terminalpp/detail/terminal_cursor_control.hpp"
#include "terminalpp/detail/terminal_control.hpp"

namespace terminalpp { namespace detail {

// ==========================================================================
// CURSOR_UP
// ==========================================================================
std::string cursor_up(
    s32                                       y,
    terminalpp::terminal::control_mode const &control_mode)
{
    std::string result = csi(control_mode);

    // If y is 1, then we can skip the amount indicator.  Note: Pretty much
    // anything that supports CUA supports the default, so this isn't checked
    // in the behaviour.
    if (y != 1)
    {
        result += std::to_string(y);
    }

    result += terminalpp::ansi::csi::CURSOR_UP;

    return result;
}

// ==========================================================================
// CURSOR_UP
// ==========================================================================
std::string cursor_down(
    s32                                       y,
    terminalpp::terminal::control_mode const &control_mode)
{
    std::string result = csi(control_mode);

    // If y is 1, then we can skip the amount indicator.  Note: Pretty much
    // anything that supports CUB supports the default, so this isn't checked
    // in the behaviour.
    if (y != 1)
    {
        result += std::to_string(y);
    }

    result += terminalpp::ansi::csi::CURSOR_DOWN;

    return result;
}

// ==========================================================================
// CURSOR_FORWARD
// ==========================================================================
std::string cursor_forward(
    s32                           x,
    terminal::control_mode const &control_mode)
{
    std::string result = csi(control_mode);

    // If x is 1, then we can skip the amount indicator.  Note: Pretty much
    // anything that supports CUF supports the default, so this isn't checked
    // in the behaviour.
    if (x != 1)
    {
        result += std::to_string(x);
    }

    result += terminalpp::ansi::csi::CURSOR_FORWARD;

    return result;
}

// ==========================================================================
// CURSOR_BACKWARD
// ==========================================================================
std::string cursor_backward(
    s32                           x,
    terminal::control_mode const &control_mode)
{
    std::string result = csi(control_mode);

    // If x is 1, then we can skip the amount indicator.  Note: Pretty much
    // anything that supports CUB supports the default, so this isn't checked
    // in the behaviour.
    if (x != 1)
    {
        result += std::to_string(x);
    }

    result += terminalpp::ansi::csi::CURSOR_BACKWARD;

    return result;
}

// ==========================================================================
// CURSOR_HORIZONTAL_ABSOLUTE
// ==========================================================================
std::string cursor_horizontal_absolute(
    s32                           x,
    terminal::behaviour const    &behaviour,
    terminal::control_mode const &control_mode)
{
    std::string result;

    result += csi(control_mode);

    // If x is 1, and our terminal supports CHA with a default argument, then
    // we can skip the character the column indicator.  Otherwise, we have to
    // include it.
    if (x != 1 || !behaviour.supports_cha_default)
    {
        result += std::to_string(x);
    }

    result += terminalpp::ansi::csi::CURSOR_HORIZONTAL_ABSOLUTE;

    return result;
}

// ==========================================================================
// CURSOR_POSITION
// ==========================================================================
std::string cursor_position(
    point                  const &pt,
    terminal::behaviour    const &behaviour,
    terminal::control_mode const &control_mode)
{
    return csi(control_mode)
         + std::to_string(pt.y)
         + terminalpp::ansi::PS
         + std::to_string(pt.x)
         + terminalpp::ansi::csi::CURSOR_POSITION;
}

}}
