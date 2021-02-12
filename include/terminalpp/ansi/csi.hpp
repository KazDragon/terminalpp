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
static constexpr byte INSERT_BLANK                     = terminalpp::detail::ascii::AT;
// Move the cursor up N rows.
static constexpr byte CURSOR_UP                        = terminalpp::detail::ascii::UPPERCASE_A;
// Move the cursor down N rows.
static constexpr byte CURSOR_DOWN                      = terminalpp::detail::ascii::UPPERCASE_B;
// Move the cursor right N columns.
static constexpr byte CURSOR_FORWARD                   = terminalpp::detail::ascii::UPPERCASE_C;
// Move the cursor left N columns.
static constexpr byte CURSOR_BACKWARD                  = terminalpp::detail::ascii::UPPERCASE_D;

// Move the cursor to the beginning of the line that is N lines down.
static constexpr byte CURSOR_NEXT_LINE                 = terminalpp::detail::ascii::UPPERCASE_E;
// Move the cursor to the beginning of the line that is N lines up.
static constexpr byte CURSOR_PREVIOUS_LINE             = terminalpp::detail::ascii::UPPERCASE_F;
// During input, this can also mean END.
static constexpr byte CURSOR_END                       = terminalpp::detail::ascii::UPPERCASE_F;
// Move to a specific column.
static constexpr byte CURSOR_HORIZONTAL_ABSOLUTE       = terminalpp::detail::ascii::UPPERCASE_G;
// Move to a specific cursor position (row,column).
static constexpr byte CURSOR_POSITION                  = terminalpp::detail::ascii::UPPERCASE_H;
// During input, this can also mean HOME.
static constexpr byte CURSOR_HOME                      = terminalpp::detail::ascii::UPPERCASE_H;
// Move forward N tabs
static constexpr byte CURSOR_TABULATION                = terminalpp::detail::ascii::UPPERCASE_I;

// Erase data.
//  0 - (Default) Clear from the cursor to the end of the screen.
//  1 - Clear from the cursor to the beginning of the screen.
//  2 - Clear the entire screen (cursor position is indeterminate).
static constexpr byte ERASE_IN_DISPLAY                 = terminalpp::detail::ascii::UPPERCASE_J;
    static constexpr byte ERASE_IN_DISPLAY_BELOW       = terminalpp::detail::ascii::ZERO;
    static constexpr byte ERASE_IN_DISPLAY_ABOVE       = terminalpp::detail::ascii::ONE;
    static constexpr byte ERASE_IN_DISPLAY_ALL         = terminalpp::detail::ascii::TWO;

// Selective Erase In Display
//  - Requires ? extender
//  - Uses same constants as Erase In Display.
static constexpr byte SELECTIVE_ERASE_IN_DISPLAY       = terminalpp::detail::ascii::UPPERCASE_J;

// Erase line
//  0 - (Default) Clear from the cursor to the end of the line.
//  1 - Clear from the cursor to the beginning of the line.
//  2 - Clear entire line (cursor position remains the same).
static constexpr byte ERASE_IN_LINE                    = terminalpp::detail::ascii::UPPERCASE_K;
    static constexpr byte ERASE_IN_LINE_RIGHT          = terminalpp::detail::ascii::ZERO;
    static constexpr byte ERASE_IN_LINE_LEFT           = terminalpp::detail::ascii::ONE;
    static constexpr byte ERASE_IN_LINE_ALL            = terminalpp::detail::ascii::TWO;

// Selective Erase In Line
//  - Requires ? extender
//  - Uses same constants as Erase In Line.
static constexpr byte SELECTIVE_ERASE_IN_LINE          = terminalpp::detail::ascii::UPPERCASE_K;

// Insert N lines
static constexpr byte INSERT_LINE                      = terminalpp::detail::ascii::UPPERCASE_L;

// Delete N lines
static constexpr byte DELETE_LINE                      = terminalpp::detail::ascii::UPPERCASE_M;

// Delete N characters
static constexpr byte DELETE_CHARACTERS                = terminalpp::detail::ascii::UPPERCASE_P;

// Sixel/ReGIS graphics
//  - Requires ? extender
static constexpr byte SIXEL_GRAPHICS                   = terminalpp::detail::ascii::UPPERCASE_S;

// Scroll up by N lines
static constexpr byte SCROLL_UP                        = terminalpp::detail::ascii::UPPERCASE_S;

// Scroll down by N lines
static constexpr byte SCROLL_DOWN                      = terminalpp::detail::ascii::UPPERCASE_T;

// Initiate Highlight Mouse Tracking
static constexpr byte HIGHLIGHT_MOUSE_TRACKING         = terminalpp::detail::ascii::UPPERCASE_T;

// Reset Title Mode Feature
//  - Requires > extender
static constexpr byte RESET_TITLE_MODE_FEATURE         = terminalpp::detail::ascii::UPPERCASE_T;

// Horizontal and Vertical position - as Cursor Position
static constexpr byte HORIZONTAL_AND_VERTICAL_POSITION = terminalpp::detail::ascii::LOWERCASE_F;

// Select graphics rendition - see graphics namespace
static constexpr byte SELECT_GRAPHICS_RENDITION        = terminalpp::detail::ascii::LOWERCASE_M;

// Mouse Tracking - see mouse namespace
static constexpr byte MOUSE_TRACKING                   = terminalpp::detail::ascii::UPPERCASE_M;

// Device status report - request requires parameter of 6, response
// requires parameters of row,column.
static constexpr byte DEVICE_STATUS_REPORT             = terminalpp::detail::ascii::LOWERCASE_N;
static constexpr byte DEVICE_STATUS_REPORT_REPLY       = terminalpp::detail::ascii::UPPERCASE_R;

// Save cursor position
static constexpr byte SAVE_CURSOR_POSITION             = terminalpp::detail::ascii::LOWERCASE_S;

// Restore (unsave) cursor
static constexpr byte RESTORE_CURSOR_POSITION          = terminalpp::detail::ascii::LOWERCASE_U;

// Erase Characters
static constexpr byte ERASE_CHARACTER                  = terminalpp::detail::ascii::UPPERCASE_X;

// Tab backwards
static constexpr byte CURSOR_BACKWARD_TABULATION       = terminalpp::detail::ascii::UPPERCASE_Z;

// Cursor Position Absolute
static constexpr byte CURSOR_POSITION_ABSOLUTE         = terminalpp::detail::ascii::GRAVE;

// Cursor Position Relative
static constexpr byte CURSOR_POSITION_RELATIVE         = terminalpp::detail::ascii::LOWERCASE_A;

// Repeat Preceding Character
static constexpr byte REPEAT_PRECEDING_CHARACTER       = terminalpp::detail::ascii::LOWERCASE_B;

// Send Device Attributes
//  - Primary Attributes has no extender
//  - Primary Response has ? extender
//  - Secondary Attributes has > extender
static constexpr byte SEND_DEVICE_ATTRIBUTES           = terminalpp::detail::ascii::LOWERCASE_C;

// Line Position Absolute
static constexpr byte LINE_POSITION_ABSOLUTE           = terminalpp::detail::ascii::LOWERCASE_D;

// Line Position Relative
static constexpr byte LINE_POSITION_RELATIVE           = terminalpp::detail::ascii::LOWERCASE_E;

// Line Position
static constexpr byte LINE_POSITION                    = terminalpp::detail::ascii::LOWERCASE_F;

// Tab Clear
static constexpr byte TAB_CLEAR                        = terminalpp::detail::ascii::LOWERCASE_G;
    static constexpr byte TAB_CLEAR_CURRENT_COLUMN     = terminalpp::detail::ascii::ZERO;
    static constexpr byte TAB_CLEAR_ALL                = terminalpp::detail::ascii::THREE;

// Set Mode
static constexpr byte SET_MODE                         = terminalpp::detail::ascii::LOWERCASE_H;

// Reset Mode
static constexpr byte RESET_MODE                       = terminalpp::detail::ascii::LOWERCASE_L;

// Keypad buttons / Function keys
static constexpr byte KEYPAD_FUNCTION                  = terminalpp::detail::ascii::TILDE;
    static constexpr std::int8_t const KEYPAD_HOME                  = 1;
    static constexpr std::int8_t const KEYPAD_INSERT                = 2;
    static constexpr std::int8_t const KEYPAD_DEL                   = 3;
    static constexpr std::int8_t const KEYPAD_END                   = 4;
    static constexpr std::int8_t const KEYPAD_PGUP                  = 5;
    static constexpr std::int8_t const KEYPAD_PGDN                  = 6;
    static constexpr std::int8_t const KEYPAD_F1                    = 11;
    static constexpr std::int8_t const KEYPAD_F2                    = 12;
    static constexpr std::int8_t const KEYPAD_F3                    = 13;
    static constexpr std::int8_t const KEYPAD_F4                    = 14;
    static constexpr std::int8_t const KEYPAD_F5                    = 15;
    static constexpr std::int8_t const KEYPAD_F6                    = 17; // Skip 16.
    static constexpr std::int8_t const KEYPAD_F7                    = 18;
    static constexpr std::int8_t const KEYPAD_F8                    = 19;
    static constexpr std::int8_t const KEYPAD_F9                    = 20;
    static constexpr std::int8_t const KEYPAD_F10                   = 21;
    static constexpr std::int8_t const KEYPAD_F11                   = 23; // Skip 22.
    static constexpr std::int8_t const KEYPAD_F12                   = 24;

// The following modifiers can apply to all keypad/function key controls.
    static constexpr std::int8_t const MODIFIER_SHIFT               = 2;
    static constexpr std::int8_t const MODIFIER_ALT                 = 3;
    static constexpr std::int8_t const MODIFIER_SHIFT_ALT           = 4;
    static constexpr std::int8_t const MODIFIER_CTRL                = 5;
    static constexpr std::int8_t const MODIFIER_SHIFT_CTRL          = 6;
    static constexpr std::int8_t const MODIFIER_ALT_CTRL            = 7;
    static constexpr std::int8_t const MODIFIER_SHIFT_ALT_CTRL      = 8;
    static constexpr std::int8_t const MODIFIER_META                = 9;
    static constexpr std::int8_t const MODIFIER_META_SHIFT          = 10;
    static constexpr std::int8_t const MODIFIER_META_ALT            = 11;
    static constexpr std::int8_t const MODIFIER_META_SHIFT_ALT      = 12;
    static constexpr std::int8_t const MODIFIER_META_CTRL           = 13;
    static constexpr std::int8_t const MODIFIER_META_SHIFT_CTRL     = 14;
    static constexpr std::int8_t const MODIFIER_META_ALT_CTRL       = 15;
    static constexpr std::int8_t const MODIFIER_META_SHIFT_ALT_CTRL = 16;

// DEC Private Mode
//  - Require ? extenders
static constexpr byte DECSET                           = terminalpp::detail::ascii::LOWERCASE_H;
static constexpr byte DECRST                           = terminalpp::detail::ascii::LOWERCASE_L;
    static constexpr byte CURSOR_STATE[]               = {terminalpp::detail::ascii::TWO,
                                                          terminalpp::detail::ascii::FIVE, 0};

// Soft Reset
//  - Requires ! extender
static constexpr byte SOFT_RESET                       = terminalpp::detail::ascii::EXCLAMATION_MARK;
}}}
