#ifndef TERMINALPP_ANSI_CSI_HPP_
#define TERMINALPP_ANSI_CSI_HPP_

#include "terminalpp/detail/ascii.hpp"
#include <string>

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

// Move to a specific column.
static char const CURSOR_HORIZONTAL_ABSOLUTE       = terminalpp::ascii::UPPERCASE_G;
// Move to a specific cursor position (row,column).
static char const CURSOR_POSITION                  = terminalpp::ascii::UPPERCASE_H;

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

// DEC Private Mode Set
static char const DECSET                           = terminalpp::ascii::LOWERCASE_H;

// DEC Private Mode Reset
static char const DECRST                           = terminalpp::ascii::LOWERCASE_L;

// For ANSI sequences of the format: ESC?x;y;zC (e.g. "ESC[10;2H"
// In the above example, "[" is the initiator, "H" is the command, and
// "10;2" is the arguments.
struct sequence
{
    std::string arguments_;
    bool        meta_;
    char        initiator_;
    char        command_;
};

constexpr inline bool operator==(sequence const& lhs, sequence const& rhs)
{
    return lhs.meta_      == rhs.meta_
        && lhs.command_   == rhs.command_
        && lhs.initiator_ == rhs.initiator_
        && lhs.arguments_ == rhs.arguments_;
}

}}}

#endif
