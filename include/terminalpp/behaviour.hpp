#pragma once

#include "terminalpp/core.hpp"

namespace terminalpp {

//* =====================================================================
/// \brief A set of flags that determine how a terminal should behave
/// over a datastream.
//* =====================================================================
struct TERMINALPP_EXPORT behaviour
{
  constexpr behaviour()
    : supports_cha(true),
      supports_cha_default(true),
      supports_vpa(true),
      supports_vpa_default(true),
      supports_cup_default_row(false),
      supports_cup_default_column(true),
      supports_cup_default_all(true),
      supports_basic_mouse_tracking(false),
      supports_all_mouse_motion_tracking(false),
      supports_window_title_bel(false),
      supports_window_title_st(false),
      unicode_in_all_charsets(false)
  {
  }

  // True if the terminal supports Cursor Horizontal Absolute
  bool supports_cha : 1;

  // True if the terminal supports the use of a default argument
  // in Cursor Horizontal Absolute
  bool supports_cha_default : 1;

  // True if the terminal supports Line Position Absolute (VPA [sic])
  bool supports_vpa : 1;

  // True if the terminal supports the use of a default argument
  // in Line Position Absolute
  bool supports_vpa_default : 1;

  // True if the terminal supports the use of a default row argument
  // (only) in Cursor Position.
  bool supports_cup_default_row : 1;

  // True if the terminal supports the use of a default column argument
  // (only) in Cursor Position.
  bool supports_cup_default_column : 1;

  // True if the terminal supports the use of both arguments being
  // default in Cursor Position
  bool supports_cup_default_all : 1;

  // True if the terminal supports basic mouse tracking.
  bool supports_basic_mouse_tracking : 1;

  // True if the terminal supports all mouse motion tracking.
  bool supports_all_mouse_motion_tracking : 1;

  // True if the window title can be set with the BEL terminator.
  bool supports_window_title_bel : 1;

  // True if the window title can be set with the ST terminator.
  bool supports_window_title_st : 1;

  // True if unicode can be used in all charsets; false if unicode
  // can only be used in the default charset;
  bool unicode_in_all_charsets : 1;
};

}  // namespace terminalpp
