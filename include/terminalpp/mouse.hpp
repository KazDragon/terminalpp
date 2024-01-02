#pragma once

#include "terminalpp/point.hpp"
#include <iosfwd>

namespace terminalpp::mouse {

enum class event_type : byte
{
  left_button_down,
  middle_button_down,
  right_button_down,
  button_up,
  no_button_change,
  scrollwheel_up,
  scrollwheel_down,
};

//* =========================================================================
/// \brief A structure that encapsulates a mouse event.
//* =========================================================================
struct TERMINALPP_EXPORT event
{
  //* =====================================================================
  /// \brief The type of action that caused this event.
  //* =====================================================================
  event_type action_ = event_type::no_button_change;

  //* =====================================================================
  /// \brief The position of the mouse in this event.
  //* =====================================================================
  point position_;

  //* =====================================================================
  /// \brief Equality operator
  //* =====================================================================
  constexpr friend bool operator==(event const &lhs, event const &rhs)
  {
    return lhs.action_ == rhs.action_ && lhs.position_ == rhs.position_;
  }
};

//* =========================================================================
/// \brief Streaming output operator
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, event const &ev);

}  // namespace terminalpp::mouse
