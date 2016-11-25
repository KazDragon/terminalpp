#pragma once

#include "terminalpp/core.hpp"
#include "terminalpp/detail/ascii.hpp"

//* =========================================================================
/// \namespace terminalpp::ansi::mouse
/// \brief Constants and structures for dealing with mouse controls.
//* =========================================================================
namespace terminalpp { namespace ansi { namespace mouse {

// Mouse values are encoded by transmitting printable characters starting
// with the space character.  This counts for both buttons and co-ordinate
// values.
static constexpr char const MOUSE_VALUE_OFFSET
    = terminalpp::detail::ascii::SPACE;

//* =========================================================================
/// \brief Structure that encapsulates a report about a mouse action.
//* =========================================================================
struct report
{
    static terminalpp::u8 const LEFT_BUTTON_DOWN   = terminalpp::u8(0);
    static terminalpp::u8 const MIDDLE_BUTTON_DOWN = terminalpp::u8(1);
    static terminalpp::u8 const RIGHT_BUTTON_DOWN  = terminalpp::u8(2);
    static terminalpp::u8 const BUTTON_UP          = terminalpp::u8(3);
    static terminalpp::u8 const NO_BUTTON_CHANGE   = terminalpp::u8(32);
    static terminalpp::u8 const SCROLLWHEEL_UP     = terminalpp::u8(64);
    static terminalpp::u8 const SCROLLWHEEL_DOWN   = terminalpp::u8(65);

    //* =====================================================================
    /// \brief The mouse button state in this report.  E.g. LEFT_BUTTON_DOWN
    /// or SCROLLWHEEL_UP.
    //* =====================================================================
    terminalpp::u8  button_;

    //* =====================================================================
    /// \brief The horizontal position of the mouse in this report.  The
    /// leftmost column is given the value 0.
    //* =====================================================================
    terminalpp::u32 x_position_;

    //* =====================================================================
    /// \brief The vertical position of the mouse in this report.  The
    /// uppermost column is given the value 0.
    //* =====================================================================
    terminalpp::u32 y_position_;
};

//* =========================================================================
/// \brief Equality operator
//* =========================================================================
constexpr inline bool operator==(report const &lhs, report const &rhs)
{
    return lhs.button_     == rhs.button_
        && lhs.x_position_ == rhs.x_position_
        && lhs.y_position_ == rhs.y_position_;
}

}}}
