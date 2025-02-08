#pragma once

#include "terminalpp/core.hpp"
#include "terminalpp/detail/ascii.hpp"

//* =========================================================================
/// \namespace terminalpp::ansi::csi
/// \brief Contains all of the constants for the commands that begin with the
/// Control Sequence Introducer sequence.
//* =========================================================================
namespace terminalpp::ansi::csi {

// clang-format off
// Insert N blank characters
inline constexpr byte insert_blank                     = terminalpp::detail::ascii::at;
// Move the cursor up N rows.
inline constexpr byte cursor_up                        = terminalpp::detail::ascii::uppercase_a;
// Move the cursor down N rows.
inline constexpr byte cursor_down                      = terminalpp::detail::ascii::uppercase_b;
// Move the cursor right N columns.
inline constexpr byte cursor_forward                   = terminalpp::detail::ascii::uppercase_c;
// Move the cursor left N columns.
inline constexpr byte cursor_backward                  = terminalpp::detail::ascii::uppercase_d;

// Move the cursor to the beginning of the line that is N lines down.
inline constexpr byte cursor_next_line                 = terminalpp::detail::ascii::uppercase_e;
// Move the cursor to the beginning of the line that is N lines up.
inline constexpr byte cursor_previous_line             = terminalpp::detail::ascii::uppercase_f;
// During input, this can also mean END.
inline constexpr byte cursor_end                       = terminalpp::detail::ascii::uppercase_f;
// Move to a specific column.
inline constexpr byte cursor_horizontal_absolute       = terminalpp::detail::ascii::uppercase_g;
// Move to a specific cursor position (row,column).
inline constexpr byte cursor_position                  = terminalpp::detail::ascii::uppercase_h;
// During input, this can also mean HOME.
inline constexpr byte cursor_home                      = terminalpp::detail::ascii::uppercase_h;
// Move forward N tabs
inline constexpr byte cursor_tabulation                = terminalpp::detail::ascii::uppercase_i;

// Erase data.
//  0 - (Default) Clear from the cursor to the end of the screen.
//  1 - Clear from the cursor to the beginning of the screen.
//  2 - Clear the entire screen (cursor position is indeterminate).
inline constexpr byte erase_in_display                 = terminalpp::detail::ascii::uppercase_j;
    inline constexpr byte erase_in_display_below       = terminalpp::detail::ascii::zero;
    inline constexpr byte erase_in_display_above       = terminalpp::detail::ascii::one;
    inline constexpr byte erase_in_display_all         = terminalpp::detail::ascii::two;

// Selective Erase In Display
//  - Requires ? extender
//  - Uses same constants as Erase In Display.
inline constexpr byte selective_erase_in_display       = terminalpp::detail::ascii::uppercase_j;

// Erase line
//  0 - (Default) Clear from the cursor to the end of the line.
//  1 - Clear from the cursor to the beginning of the line.
//  2 - Clear entire line (cursor position remains the same).
inline constexpr byte erase_in_line                    = terminalpp::detail::ascii::uppercase_k;
    inline constexpr byte erase_in_line_right          = terminalpp::detail::ascii::zero;
    inline constexpr byte erase_in_line_left           = terminalpp::detail::ascii::one;
    inline constexpr byte erase_in_line_all            = terminalpp::detail::ascii::two;

// Selective Erase In Line
//  - Requires ? extender
//  - Uses same constants as Erase In Line.
inline constexpr byte selective_erase_in_line          = terminalpp::detail::ascii::uppercase_k;

// Insert N lines
inline constexpr byte insert_line                      = terminalpp::detail::ascii::uppercase_l;

// Delete N lines
inline constexpr byte delete_line                      = terminalpp::detail::ascii::uppercase_m;

// Delete N characters
inline constexpr byte delete_characters                = terminalpp::detail::ascii::uppercase_p;

// Sixel/ReGIS graphics
//  - Requires ? extender
inline constexpr byte sixel_graphics                   = terminalpp::detail::ascii::uppercase_s;

// Scroll up by N lines
inline constexpr byte scroll_up                        = terminalpp::detail::ascii::uppercase_s;

// Scroll down by N lines
inline constexpr byte scroll_down                      = terminalpp::detail::ascii::uppercase_t;

// Initiate Highlight Mouse Tracking
inline constexpr byte highlight_mouse_tracking         = terminalpp::detail::ascii::uppercase_t;

// Reset Title Mode Feature
//  - Requires > extender
inline constexpr byte reset_title_mode_feature         = terminalpp::detail::ascii::uppercase_t;

// Horizontal and Vertical position - as Cursor Position
inline constexpr byte horizontal_and_vertical_position = terminalpp::detail::ascii::lowercase_f;

// Select graphics rendition - see graphics namespace
inline constexpr byte select_graphics_rendition        = terminalpp::detail::ascii::lowercase_m;

// Mouse Tracking - see mouse namespace
inline constexpr byte mouse_tracking                   = terminalpp::detail::ascii::uppercase_m;

// Device status report - request requires parameter of 6, response
// requires parameters of row,column.
inline constexpr byte device_status_report             = terminalpp::detail::ascii::lowercase_n;
inline constexpr byte device_status_report_reply       = terminalpp::detail::ascii::uppercase_r;

// Save cursor position
inline constexpr byte save_cursor_position             = terminalpp::detail::ascii::lowercase_s;

// Restore (unsave) cursor
inline constexpr byte restore_cursor_position          = terminalpp::detail::ascii::lowercase_u;

// Erase Characters
inline constexpr byte erase_character                  = terminalpp::detail::ascii::uppercase_x;

// Tab backwards
inline constexpr byte cursor_backward_tabulation       = terminalpp::detail::ascii::uppercase_z;

// Cursor Position Absolute
inline constexpr byte cursor_position_absolute         = terminalpp::detail::ascii::grave;

// Cursor Position Relative
inline constexpr byte cursor_position_relative         = terminalpp::detail::ascii::lowercase_a;

// Repeat Preceding Character
inline constexpr byte repeat_preceding_character       = terminalpp::detail::ascii::lowercase_b;

// Send Device Attributes
//  - Primary Attributes has no extender
//  - Primary Response has ? extender
//  - Secondary Attributes has > extender
inline constexpr byte send_device_attributes           = terminalpp::detail::ascii::lowercase_c;

// Line Position Absolute
inline constexpr byte line_position_absolute           = terminalpp::detail::ascii::lowercase_d;

// Line Position Relative
inline constexpr byte line_position_relative           = terminalpp::detail::ascii::lowercase_e;

// Line Position
inline constexpr byte line_position                    = terminalpp::detail::ascii::lowercase_f;

// Tab Clear
inline constexpr byte tab_clear                        = terminalpp::detail::ascii::lowercase_g;
    inline constexpr byte tab_clear_current_column     = terminalpp::detail::ascii::zero;
    inline constexpr byte tab_clear_all                = terminalpp::detail::ascii::three;

// Set Mode
inline constexpr byte set_mode                         = terminalpp::detail::ascii::lowercase_h;

// Reset Mode
inline constexpr byte reset_mode                       = terminalpp::detail::ascii::lowercase_l;

// Keypad buttons / Function keys
inline constexpr byte keypad_function                  = terminalpp::detail::ascii::tilde;
    inline constexpr byte keypad_home                  = 1;
    inline constexpr byte keypad_insert                = 2;
    inline constexpr byte keypad_del                   = 3;
    inline constexpr byte keypad_end                   = 4;
    inline constexpr byte keypad_pgup                  = 5;
    inline constexpr byte keypad_pgdn                  = 6;
    inline constexpr byte keypad_f1                    = 11;
    inline constexpr byte keypad_f2                    = 12;
    inline constexpr byte keypad_f3                    = 13;
    inline constexpr byte keypad_f4                    = 14;
    inline constexpr byte keypad_f5                    = 15;
    inline constexpr byte keypad_f6                    = 17; // Skip 16.
    inline constexpr byte keypad_f7                    = 18;
    inline constexpr byte keypad_f8                    = 19;
    inline constexpr byte keypad_f9                    = 20;
    inline constexpr byte keypad_f10                   = 21;
    inline constexpr byte keypad_f11                   = 23; // Skip 22.
    inline constexpr byte keypad_f12                   = 24;

// The following modifiers can apply to all keypad/function key controls.
    inline constexpr byte modifier_shift               = 2;
    inline constexpr byte modifier_alt                 = 3;
    inline constexpr byte modifier_shift_alt           = 4;
    inline constexpr byte modifier_ctrl                = 5;
    inline constexpr byte modifier_shift_ctrl          = 6;
    inline constexpr byte modifier_alt_ctrl            = 7;
    inline constexpr byte modifier_shift_alt_ctrl      = 8;
    inline constexpr byte modifier_meta                = 9;
    inline constexpr byte modifier_meta_shift          = 10;
    inline constexpr byte modifier_meta_alt            = 11;
    inline constexpr byte modifier_meta_shift_alt      = 12;
    inline constexpr byte modifier_meta_ctrl           = 13;
    inline constexpr byte modifier_meta_shift_ctrl     = 14;
    inline constexpr byte modifier_meta_alt_ctrl       = 15;
    inline constexpr byte modifier_meta_shift_alt_ctrl = 16;

// DEC Private Mode
//  - Require ? extenders
inline constexpr byte decset                           = terminalpp::detail::ascii::lowercase_h;
inline constexpr byte decrst                           = terminalpp::detail::ascii::lowercase_l;
    inline constexpr byte cursor_state[]               = {terminalpp::detail::ascii::two,
                                                          terminalpp::detail::ascii::five, 0};

// Soft Reset
//  - Requires ! extender
inline constexpr byte soft_reset                       = terminalpp::detail::ascii::exclamation_mark;
// clang-format on

}  // namespace terminalpp::ansi::csi
