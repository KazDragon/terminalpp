// ==========================================================================
// Terminal++ ANSI Protocol.
//
// Copyright (C) 2010 Matthew Chaplain, All Rights Reserved.
//
// Permission to reproduce, distribute, perform, display, and to prepare
// derivitive works from this file under the following conditions:
//
// 1. Any copy, reproduction or derivitive work of any part of this file
//    contains this copyright notice and licence in its entirety.
//
// 2. The rights granted to you under this license automatically terminate
//    should you attempt to assert any patent claims against the licensor
//    or contributors, which in any way restrict the ability of any party
//    from using this software or portions thereof in any form under the
//    terms of this license.
//
// Disclaimer: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
//             KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//             WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
//             PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
//             OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
//             OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
//             OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//             SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// ==========================================================================
#ifndef TERMINALPP_ANSI_PROTOCOL_HPP_
#define TERMINALPP_ANSI_PROTOCOL_HPP_

#include "terminalpp/core.hpp"
#include "terminalpp/ascii/protocol.hpp"
#include <boost/utility.hpp>
#include <string>

namespace terminalpp { namespace ansi {
    static char const BEL                              = 0x07;

    // The generic formula for an ANSI escape code is:
    //   ESCAPE '[' [arg [;arg...]] COMMAND
    // where ESCAPE is character 27, the '[' character is the "control sequence
    // introducer" (which can be overridden in termcap), the arguments are 
    // usually numeric and separated by semi-colons, and COMMAND is a single
    // letter that states the purpose of the sequence.

    static char const ESCAPE                           = ::terminalpp::ascii::ESC;
    static char const CONTROL_SEQUENCE_INTRODUCER      = terminalpp::ascii::OPEN_SQUARE_BRACKET;
    static char const OPERATING_SYSTEM_COMMAND         = terminalpp::ascii::CLOSE_SQUARE_BRACKET;
    static char const PRIVATE_MODE_SET                 = terminalpp::ascii::QUESTION_MARK;
    static char const PARAMETER_SEPARATOR              = terminalpp::ascii::SEMI_COLON;
    static char const SINGLE_SHIFT_SELECT_G2           = terminalpp::ascii::UPPERCASE_N;
    static char const SINGLE_SHIFT_SELECT_G3           = terminalpp::ascii::UPPERCASE_O;

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
    static char const ERASE_DATA                       = terminalpp::ascii::UPPERCASE_J;

    // Erase line
    //  0 - (Default) Clear from the cursor to the end of the line.
    //  1 - Clear from the cursor to the beginning of the line.
    //  2 - Clear entire line (cursor position remains the same).
    static char const ERASE_LINE                       = terminalpp::ascii::UPPERCASE_K;

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

// Namespace for Select Graphics Rendition parameters
namespace graphics {

    static char const NO_ATTRIBUTES                     = 0;

    enum class intensity : char
    {
        bold                                            = 1,
        faint                                           = 2,
        normal                                          = 22,
    };

    enum class underlining : char
    {
        underlined                                      = 4,
        not_underlined                                  = 24,
    };

    enum class blinking : char
    {
        blink                                           = 5,
        steady                                          = 25,
    };

    static char const FOREGROUND_COLOUR_BASE            = 30;
    static char const BACKGROUND_COLOUR_BASE            = 40;

    enum class colour : char
    {
        black                                           = 0,
        red                                             = 1,
        green                                           = 2,
        yellow                                          = 3,
        blue                                            = 4,
        magenta                                         = 5,
        cyan                                            = 6,
        white                                           = 7,
        default_                                        = 9,
    };

    enum class polarity : char
    {
        negative                                        = 7,
        positive                                        = 27,
    };
}

namespace character_set {
    // Note: For extended ASCII, both PuTTY and TeraTerm support
    // SCO+G0.
    static char const LOCALE_DEC                   = terminalpp::ascii::ZERO;
    static char const LOCALE_UK                    = terminalpp::ascii::UPPERCASE_A;
    static char const LOCALE_US_ASCII              = terminalpp::ascii::UPPERCASE_B;
    static char const LOCALE_SCO                   = terminalpp::ascii::UPPERCASE_U;

    static char const CHARACTER_SET_G0             = terminalpp::ascii::OPEN_BRACKET;
    static char const CHARACTER_SET_G1             = terminalpp::ascii::CLOSE_BRACKET;
}

namespace ss3 {
    // specific control codes for Single Shift Select of character set G3
    static char const HOME                         = terminalpp::ascii::UPPERCASE_H;
    static char const END                          = terminalpp::ascii::UPPERCASE_F;
}

// For ANSI sequences of the format: ESC[x;y;zC (e.g. "ESC[10;2H"
// In the above example, "[" is the initiator, "H" is the command, and
// "10;2" is the arguments.
struct control_sequence
{
    std::string arguments_;
    bool        meta_;
    char        initiator_;
    char        command_;
};

// Mouse
struct mouse_report
{
    static terminalpp::u8 const LEFT_BUTTON_DOWN   = terminalpp::u8(0);
    static terminalpp::u8 const MIDDLE_BUTTON_DOWN = terminalpp::u8(1);
    static terminalpp::u8 const RIGHT_BUTTON_DOWN  = terminalpp::u8(2);
    static terminalpp::u8 const BUTTON_UP          = terminalpp::u8(3);
    static terminalpp::u8 const SCROLLWHEEL_UP     = terminalpp::u8(32);
    static terminalpp::u8 const SCROLLWHEEL_DOWN   = terminalpp::u8(33);

    terminalpp::u8  button_;
    terminalpp::s32 x_position_;
    terminalpp::s32 y_position_;
};

constexpr inline bool operator==(control_sequence const& lhs, control_sequence const& rhs)
{
    return lhs.meta_      == rhs.meta_
        && lhs.command_   == rhs.command_
        && lhs.initiator_ == rhs.initiator_
        && lhs.arguments_ == rhs.arguments_;
}

constexpr inline bool operator==(mouse_report const &lhs, mouse_report const &rhs)
{
    return lhs.button_     == rhs.button_
        && lhs.x_position_ == rhs.x_position_
        && lhs.y_position_ == rhs.y_position_;
}

}}


#endif

