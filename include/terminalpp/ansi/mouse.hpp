#pragma once

#include "terminalpp/core.hpp"
#include "terminalpp/detail/ascii.hpp"
#include <iosfwd>

//* =========================================================================
/// \namespace terminalpp::ansi::mouse
/// \brief Constants and structures for dealing with mouse controls.
//* =========================================================================
namespace terminalpp { namespace ansi { namespace mouse {

// Mouse values are encoded by transmitting printable characters starting
// with the space character.  This counts for both buttons and co-ordinate
// values.
static constexpr byte const MOUSE_VALUE_OFFSET
    = terminalpp::detail::ascii::SPACE;

//* =========================================================================
/// \brief Structure that encapsulates a report about a mouse action.
//* =========================================================================
struct TERMINALPP_EXPORT report
{
    static constexpr byte LEFT_BUTTON_DOWN   = byte(0);
    static constexpr byte MIDDLE_BUTTON_DOWN = byte(1);
    static constexpr byte RIGHT_BUTTON_DOWN  = byte(2);
    static constexpr byte BUTTON_UP          = byte(3);
    static constexpr byte NO_BUTTON_CHANGE   = byte(32);
    static constexpr byte SCROLLWHEEL_UP     = byte(64);
    static constexpr byte SCROLLWHEEL_DOWN   = byte(65);

    //* =====================================================================
    /// \brief The mouse button state in this report.  E.g. LEFT_BUTTON_DOWN
    /// or SCROLLWHEEL_UP.
    //* =====================================================================
    byte  button_ = NO_BUTTON_CHANGE;

    //* =====================================================================
    /// \brief The horizontal position of the mouse in this report.  The
    /// leftmost column is given the value 0.
    //* =====================================================================
    coordinate_type x_position_ = 0;

    //* =====================================================================
    /// \brief The vertical position of the mouse in this report.  The
    /// uppermost column is given the value 0.
    //* =====================================================================
    coordinate_type y_position_ = 0;
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

//* =========================================================================
/// \brief Streaming output operator
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, report const &rep);

}}}
