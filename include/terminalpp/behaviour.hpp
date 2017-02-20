#pragma once

namespace terminalpp {

//* =====================================================================
/// \brief A set of flags that determine how a terminal should behave
/// over a datastream.
//* =====================================================================
struct behaviour
{
    constexpr behaviour()
      : can_use_eight_bit_control_codes(false),
        uses_eight_bit_control_codes_by_default(false),
        supports_cha(true),
        supports_cha_default(true),
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

    // Eight bit control codes save on a character each time an ANSI
    // control code is used.  This could amount to quite the saving over
    // time.
    bool can_use_eight_bit_control_codes : 1;

    // If a terminal can use eight bit control codes, it may require a
    // code to enable that sequence.  Some terminals may default to using
    // eight bit control codes, but not understand the enable sequence, so
    // it should only be used if actually required.
    bool uses_eight_bit_control_codes_by_default : 1;

    // True if the terminal supports Cursor Horizontal Absolute
    bool supports_cha : 1;

    // True if the terminal supports the use of a default argument
    // in Cursor Horizontal Absolute
    bool supports_cha_default : 1;

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

}
