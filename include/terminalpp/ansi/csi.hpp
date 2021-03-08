#pragma once

#include "terminalpp/detail/ascii.hpp"
#include "terminalpp/core.hpp"

//* =========================================================================
/// \namespace terminalpp::ansi::csi
/// \brief Contains all of the constants for the commands that begin with the
/// Control Sequence Introducer sequence.
//* =========================================================================
namespace terminalpp { namespace ansi { namespace csi {

// Insert N blank characters
static constexpr byte insert_blank                     = terminalpp::detail::ascii::at;
// Move the cursor up N rows.
static constexpr byte cursor_up                        = terminalpp::detail::ascii::uppercase_a;
// Move the cursor down N rows.
static constexpr byte cursor_down                      = terminalpp::detail::ascii::uppercase_b;
// Move the cursor right N columns.
static constexpr byte cursor_forward                   = terminalpp::detail::ascii::uppercase_c;
// Move the cursor left N columns.
static constexpr byte cursor_backward                  = terminalpp::detail::ascii::uppercase_d;

// Move the cursor to the beginning of the line that is N lines down.
static constexpr byte cursor_next_line                 = terminalpp::detail::ascii::uppercase_e;
// Move the cursor to the beginning of the line that is N lines up.
static constexpr byte cursor_previous_line             = terminalpp::detail::ascii::uppercase_f;
// During input, this can also mean END.
static constexpr byte cursor_end                       = terminalpp::detail::ascii::uppercase_f;
// Move to a specific column.
static constexpr byte cursor_horizontal_absolute       = terminalpp::detail::ascii::uppercase_g;
// Move to a specific cursor position (row,column).
static constexpr byte cursor_position                  = terminalpp::detail::ascii::uppercase_h;
// During input, this can also mean HOME.
static constexpr byte cursor_home                      = terminalpp::detail::ascii::uppercase_h;
// Move forward N tabs
static constexpr byte cursor_tabulation                = terminalpp::detail::ascii::uppercase_i;

// Erase data.
//  0 - (Default) Clear from the cursor to the end of the screen.
//  1 - Clear from the cursor to the beginning of the screen.
//  2 - Clear the entire screen (cursor position is indeterminate).
static constexpr byte erase_in_display                 = terminalpp::detail::ascii::uppercase_j;
    static constexpr byte erase_in_display_below       = terminalpp::detail::ascii::zero;
    static constexpr byte erase_in_display_above       = terminalpp::detail::ascii::one;
    static constexpr byte erase_in_display_all         = terminalpp::detail::ascii::two;

// Selective Erase In Display
//  - Requires ? extender
//  - Uses same constants as Erase In Display.
static constexpr byte selective_erase_in_display       = terminalpp::detail::ascii::uppercase_j;

// Erase line
//  0 - (Default) Clear from the cursor to the end of the line.
//  1 - Clear from the cursor to the beginning of the line.
//  2 - Clear entire line (cursor position remains the same).
static constexpr byte erase_in_line                    = terminalpp::detail::ascii::uppercase_k;
    static constexpr byte erase_in_line_right          = terminalpp::detail::ascii::zero;
    static constexpr byte erase_in_line_left           = terminalpp::detail::ascii::one;
    static constexpr byte erase_in_line_all            = terminalpp::detail::ascii::two;

// Selective Erase In Line
//  - Requires ? extender
//  - Uses same constants as Erase In Line.
static constexpr byte selective_erase_in_line          = terminalpp::detail::ascii::uppercase_k;

// Insert N lines
static constexpr byte insert_line                      = terminalpp::detail::ascii::uppercase_l;

// Delete N lines
static constexpr byte delete_line                      = terminalpp::detail::ascii::uppercase_m;

// Delete N characters
static constexpr byte delete_characters                = terminalpp::detail::ascii::uppercase_p;

// Sixel/ReGIS graphics
//  - Requires ? extender
static constexpr byte sixel_graphics                   = terminalpp::detail::ascii::uppercase_s;

// Scroll up by N lines
static constexpr byte scroll_up                        = terminalpp::detail::ascii::uppercase_s;

// Scroll down by N lines
static constexpr byte scroll_down                      = terminalpp::detail::ascii::uppercase_t;

// Initiate Highlight Mouse Tracking
static constexpr byte highlight_mouse_tracking         = terminalpp::detail::ascii::uppercase_t;

// Reset Title Mode Feature
//  - Requires > extender
static constexpr byte reset_title_mode_feature         = terminalpp::detail::ascii::uppercase_t;

// Horizontal and Vertical position - as Cursor Position
static constexpr byte horizontal_and_vertical_position = terminalpp::detail::ascii::lowercase_f;

// Select graphics rendition - see graphics namespace
static constexpr byte select_graphics_rendition        = terminalpp::detail::ascii::lowercase_m;

// Mouse Tracking - see mouse namespace
static constexpr byte mouse_tracking                   = terminalpp::detail::ascii::uppercase_m;

// Device status report - request requires parameter of 6, response
// requires parameters of row,column.
static constexpr byte device_status_report             = terminalpp::detail::ascii::lowercase_n;
static constexpr byte device_status_report_reply       = terminalpp::detail::ascii::uppercase_r;

// Save cursor position
static constexpr byte save_cursor_position             = terminalpp::detail::ascii::lowercase_s;

// Restore (unsave) cursor
static constexpr byte restore_cursor_position          = terminalpp::detail::ascii::lowercase_u;

// Erase Characters
static constexpr byte erase_character                  = terminalpp::detail::ascii::uppercase_x;

// Tab backwards
static constexpr byte cursor_backward_tabulation       = terminalpp::detail::ascii::uppercase_z;

// Cursor Position Absolute
static constexpr byte cursor_position_absolute         = terminalpp::detail::ascii::grave;

// Cursor Position Relative
static constexpr byte cursor_position_relative         = terminalpp::detail::ascii::lowercase_a;

// Repeat Preceding Character
static constexpr byte repeat_preceding_character       = terminalpp::detail::ascii::lowercase_b;

// Send Device Attributes
//  - Primary Attributes has no extender
//  - Primary Response has ? extender
//  - Secondary Attributes has > extender
static constexpr byte send_device_attributes           = terminalpp::detail::ascii::lowercase_c;

// Line Position Absolute
static constexpr byte line_position_absolute           = terminalpp::detail::ascii::lowercase_d;

// Line Position Relative
static constexpr byte line_position_relative           = terminalpp::detail::ascii::lowercase_e;

// Line Position
static constexpr byte line_position                    = terminalpp::detail::ascii::lowercase_f;

// Tab Clear
static constexpr byte tab_clear                        = terminalpp::detail::ascii::lowercase_g;
    static constexpr byte tab_clear_current_column     = terminalpp::detail::ascii::zero;
    static constexpr byte tab_clear_all                = terminalpp::detail::ascii::three;

// Set Mode
static constexpr byte set_mode                         = terminalpp::detail::ascii::lowercase_h;

// Reset Mode
static constexpr byte reset_mode                       = terminalpp::detail::ascii::lowercase_l;

// Keypad buttons / Function keys
static constexpr byte keypad_function                  = terminalpp::detail::ascii::tilde;
    static constexpr byte keypad_home                  = 1;
    static constexpr byte keypad_insert                = 2;
    static constexpr byte keypad_del                   = 3;
    static constexpr byte keypad_end                   = 4;
    static constexpr byte keypad_pgup                  = 5;
    static constexpr byte keypad_pgdn                  = 6;
    static constexpr byte keypad_f1                    = 11;
    static constexpr byte keypad_f2                    = 12;
    static constexpr byte keypad_f3                    = 13;
    static constexpr byte keypad_f4                    = 14;
    static constexpr byte keypad_f5                    = 15;
    static constexpr byte keypad_f6                    = 17; // Skip 16.
    static constexpr byte keypad_f7                    = 18;
    static constexpr byte keypad_f8                    = 19;
    static constexpr byte keypad_f9                    = 20;
    static constexpr byte keypad_f10                   = 21;
    static constexpr byte keypad_f11                   = 23; // Skip 22.
    static constexpr byte keypad_f12                   = 24;

// The following modifiers can apply to all keypad/function key controls.
    static constexpr byte modifier_shift               = 2;
    static constexpr byte modifier_alt                 = 3;
    static constexpr byte modifier_shift_alt           = 4;
    static constexpr byte modifier_ctrl                = 5;
    static constexpr byte modifier_shift_ctrl          = 6;
    static constexpr byte modifier_alt_ctrl            = 7;
    static constexpr byte modifier_shift_alt_ctrl      = 8;
    static constexpr byte modifier_meta                = 9;
    static constexpr byte modifier_meta_shift          = 10;
    static constexpr byte modifier_meta_alt            = 11;
    static constexpr byte modifier_meta_shift_alt      = 12;
    static constexpr byte modifier_meta_ctrl           = 13;
    static constexpr byte modifier_meta_shift_ctrl     = 14;
    static constexpr byte modifier_meta_alt_ctrl       = 15;
    static constexpr byte modifier_meta_shift_alt_ctrl = 16;

// DEC Private Mode
//  - Require ? extenders
static constexpr byte decset                           = terminalpp::detail::ascii::lowercase_h;
static constexpr byte decrst                           = terminalpp::detail::ascii::lowercase_l;
    static constexpr byte cursor_state[]               = {terminalpp::detail::ascii::two,
                                                          terminalpp::detail::ascii::five, 0};

// Soft Reset
//  - Requires ! extender
static constexpr byte soft_reset                       = terminalpp::detail::ascii::exclamation_mark;
}}}
