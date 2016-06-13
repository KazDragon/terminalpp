#pragma once

#include "terminalpp/detail/ascii.hpp"
#include "terminalpp/core.hpp"

namespace terminalpp { namespace ansi { namespace csi {

// Move the cursor up N rows.
static char const CURSOR_UP                        = terminalpp::ascii::UPPERCASE_A;
// Move the cursor down N rows.
static char const CURSOR_DOWN                      = terminalpp::ascii::UPPERCASE_B;
// Move the cursor right N columns.
static char const CURSOR_FORWARD                   = terminalpp::ascii::UPPERCASE_C;
// Move the cursor left N columns.
static char const CURSOR_BACKWARD                  = terminalpp::ascii::UPPERCASE_D;

// Move the cursor to the beginning of the line that is N lines down.
static char const CURSOR_NEXT_LINE                 = terminalpp::ascii::UPPERCASE_E;
// Move the cursor to the beginning of the line that is N lines up.
static char const CURSOR_PREVIOUS_LINE             = terminalpp::ascii::UPPERCASE_F;
// Durin input, this can also mean END.
static char const CURSOR_END                       = terminalpp::ascii::UPPERCASE_F;
// Move to a specific column.
static char const CURSOR_HORIZONTAL_ABSOLUTE       = terminalpp::ascii::UPPERCASE_G;
// Move to a specific cursor position (row,column).
static char const CURSOR_POSITION                  = terminalpp::ascii::UPPERCASE_H;
// During input, this can also mean HOME.
static char const CURSOR_HOME                      = terminalpp::ascii::UPPERCASE_H;
// Move forward N tabs
static char const CURSOR_TABULATION                = terminalpp::ascii::UPPERCASE_I;

// Erase data.
//  0 - (Default) Clear from the cursor to the end of the screen.
//  1 - Clear from the cursor to the beginning of the screen.
//  2 - Clear the entire screen (cursor position is indeterminate).
static char const ERASE_IN_DISPLAY                 = terminalpp::ascii::UPPERCASE_J;
    static char const ERASE_IN_DISPLAY_BELOW       = terminalpp::ascii::ZERO;
    static char const ERASE_IN_DISPLAY_ABOVE       = terminalpp::ascii::ONE;
    static char const ERASE_IN_DISPLAY_ALL         = terminalpp::ascii::TWO;

// Erase line
//  0 - (Default) Clear from the cursor to the end of the line.
//  1 - Clear from the cursor to the beginning of the line.
//  2 - Clear entire line (cursor position remains the same).
static char const ERASE_IN_LINE                    = terminalpp::ascii::UPPERCASE_K;
    static char const ERASE_IN_LINE_RIGHT          = terminalpp::ascii::ZERO;
    static char const ERASE_IN_LINE_LEFT           = terminalpp::ascii::ONE;
    static char const ERASE_IN_LINE_ALL            = terminalpp::ascii::TWO;

// Scroll up by N lines
static char const SCROLL_UP                        = terminalpp::ascii::UPPERCASE_S;

// Scroll down by N lines
static char const SCROLL_DOWN                      = terminalpp::ascii::UPPERCASE_T;

// Horizontal and Vertical position - as Cursor Position
static char const HORIZONTAL_AND_VERTICAL_POSITION = terminalpp::ascii::LOWERCASE_F;

// Select graphics rendition - see graphics namespace
static char const SELECT_GRAPHICS_RENDITION        = terminalpp::ascii::LOWERCASE_M;

// Mouse Tracking - see mouse namespace
static char const MOUSE_TRACKING                   = terminalpp::ascii::UPPERCASE_M;

// Device status report - request requires parameter of 6, response
// requires parameters of row,column.
static char const DEVICE_STATUS_REPORT             = terminalpp::ascii::LOWERCASE_N;
static char const DEVICE_STATUS_REPORT_REPLY       = terminalpp::ascii::UPPERCASE_R;

// Save cursor position
static char const SAVE_CURSOR_POSITION             = terminalpp::ascii::LOWERCASE_S;

// Restore (unsave) cursor
static char const RESTORE_CURSOR_POSITION          = terminalpp::ascii::LOWERCASE_U;

// Erase Characters
static char const ERASE_CHARACTER                  = terminalpp::ascii::UPPERCASE_X;

// Tab backwards
static char const CURSOR_BACKWARD_TABULATION       = terminalpp::ascii::UPPERCASE_Z;

// Keypad buttons / Function keys
static char const KEYPAD_FUNCTION                  = terminalpp::ascii::TILDE;
    static u8 const KEYPAD_HOME                    = 1;
    static u8 const KEYPAD_INSERT                  = 2;
    static u8 const KEYPAD_DEL                     = 3;
    static u8 const KEYPAD_END                     = 4;
    static u8 const KEYPAD_PGUP                    = 5;
    static u8 const KEYPAD_PGDN                    = 6;
    static u8 const KEYPAD_F1                      = 11;
    static u8 const KEYPAD_F2                      = 12;
    static u8 const KEYPAD_F3                      = 13;
    static u8 const KEYPAD_F4                      = 14;
    static u8 const KEYPAD_F5                      = 15;
    static u8 const KEYPAD_F6                      = 17; // Skip 16.
    static u8 const KEYPAD_F7                      = 18;
    static u8 const KEYPAD_F8                      = 19;
    static u8 const KEYPAD_F9                      = 20;
    static u8 const KEYPAD_F10                     = 21;
    static u8 const KEYPAD_F11                     = 23; // Skip 22.
    static u8 const KEYPAD_F12                     = 24;

// The following modifiers can apply to all keypad/function key controls.
    static u8 const MODIFIER_SHIFT                 = 2;
    static u8 const MODIFIER_ALT                   = 3;
    static u8 const MODIFIER_SHIFT_ALT             = 4;
    static u8 const MODIFIER_CTRL                  = 5;
    static u8 const MODIFIER_SHIFT_CTRL            = 6;
    static u8 const MODIFIER_ALT_CTRL              = 7;
    static u8 const MODIFIER_SHIFT_ALT_CTRL        = 8;
    static u8 const MODIFIER_META                  = 9;
    static u8 const MODIFIER_META_SHIFT            = 10;
    static u8 const MODIFIER_META_ALT              = 11;
    static u8 const MODIFIER_META_SHIFT_ALT        = 12;
    static u8 const MODIFIER_META_CTRL             = 13;
    static u8 const MODIFIER_META_SHIFT_CTRL       = 14;
    static u8 const MODIFIER_META_ALT_CTRL         = 15;
    static u8 const MODIFIER_META_SHIFT_ALT_CTRL   = 16;

// DEC Private Mode
static char const DECSET                           = terminalpp::ascii::LOWERCASE_H;
static char const DECRST                           = terminalpp::ascii::LOWERCASE_L;
    static char const CURSOR_STATE[]               = {terminalpp::ascii::TWO,
                                                      terminalpp::ascii::FIVE, 0};

}}}
