#pragma once

//* =========================================================================
/// \namespace terminalpp::detail::ascii
/// \brief A namespace for constants representing the ASCII character set.
//* =========================================================================
namespace terminalpp { namespace detail { namespace ascii {

// Source: http://ascii-table.com/ascii.php

// Control Code Block
static constexpr byte NUL = 0;   // NULL
static constexpr byte SOH = 1;   // Start Of Header
static constexpr byte STX = 2;   // Start Of Text
static constexpr byte ETX = 3;   // End Of Text
static constexpr byte EOT = 4;   // End Of Transmission
static constexpr byte ENQ = 5;   // Enquiry
static constexpr byte ACK = 6;   // Acknowledge
static constexpr byte BEL = 7;   // Bell
static constexpr byte BS  = 8;   // Backspace
static constexpr byte HT  = 9;   // Horizontal Tabulation
static constexpr byte LF  = 10;  // Line Feed
static constexpr byte VT  = 11;  // Vertical Tabulation
static constexpr byte FF  = 12;  // Form Feed
static constexpr byte CR  = 13;  // Carriage Return
static constexpr byte SO  = 14;  // Shift Out
static constexpr byte SI  = 15;  // Shift In
static constexpr byte DLE = 16;  // Data Link Escape
static constexpr byte DC1 = 17;  // Device Control 1 (XON)
static constexpr byte DC2 = 18;  // Device Control 2
static constexpr byte DC3 = 19;  // Device Control 3 (XOFF)
static constexpr byte DC4 = 20;  // Device Control 4
static constexpr byte NAK = 21;  // Negative Acknowledge
static constexpr byte SYN = 22;  // Synchronous Idle
static constexpr byte ETB = 23;  // End Of Transmission Block
static constexpr byte CAN = 24;  // Cancel
static constexpr byte EM  = 25;  // End Of Medium
static constexpr byte SUB = 26;  // Substitute
static constexpr byte ESC = 27;  // Escape
static constexpr byte FS  = 28;  // File Separator
static constexpr byte GS  = 29;  // Group Separator
static constexpr byte RS  = 30;  // Record Separator
static constexpr byte US  = 31;  // Unit Separator

// Printable Character Block
static constexpr byte SPACE                 = 32;  // [SPACE]
static constexpr byte EXCLAMATION_MARK      = 33;  // !
static constexpr byte QUOTES                = 34;  // "
static constexpr byte HASH                  = 35;  // #
static constexpr byte DOLLAR                = 36;  // $
static constexpr byte PERCENT               = 37;  // %
static constexpr byte AMPERSAND             = 38;  // %
static constexpr byte APOSTROPHE            = 39;  // '
static constexpr byte OPEN_PARENTHESIS      = 40;  // (
static constexpr byte CLOSE_PARENTHESIS     = 41;  // )
static constexpr byte ASTERISK              = 42;  // *
static constexpr byte PLUS                  = 43;  // +
static constexpr byte COMMA                 = 44;  // ,
static constexpr byte MINUS                 = 45;  // -
static constexpr byte FULL_STOP             = 46;  // .
static constexpr byte SLASH                 = 47;  // /
static constexpr byte ZERO                  = 48;  // 0
static constexpr byte ONE                   = 49;  // 1
static constexpr byte TWO                   = 50;  // 2
static constexpr byte THREE                 = 51;  // 3
static constexpr byte FOUR                  = 52;  // 4
static constexpr byte FIVE                  = 53;  // 5
static constexpr byte SIX                   = 54;  // 6
static constexpr byte SEVEN                 = 55;  // 7
static constexpr byte EIGHT                 = 56;  // 8
static constexpr byte NINE                  = 57;  // 9
static constexpr byte COLON                 = 58;  // :
static constexpr byte SEMI_COLON            = 59;  // ;
static constexpr byte LESS_THAN             = 60;  // <
static constexpr byte EQUALS                = 61;  // =
static constexpr byte GREATER_THAN          = 62;  // >
static constexpr byte QUESTION_MARK         = 63;  // ?
static constexpr byte AT                    = 64;  // @
static constexpr byte UPPERCASE_A           = 65;  // A
static constexpr byte UPPERCASE_B           = 66;  // B
static constexpr byte UPPERCASE_C           = 67;  // C
static constexpr byte UPPERCASE_D           = 68;  // D
static constexpr byte UPPERCASE_E           = 69;  // E
static constexpr byte UPPERCASE_F           = 70;  // F
static constexpr byte UPPERCASE_G           = 71;  // G
static constexpr byte UPPERCASE_H           = 72;  // H
static constexpr byte UPPERCASE_I           = 73;  // I
static constexpr byte UPPERCASE_J           = 74;  // J
static constexpr byte UPPERCASE_K           = 75;  // K
static constexpr byte UPPERCASE_L           = 76;  // L
static constexpr byte UPPERCASE_M           = 77;  // M
static constexpr byte UPPERCASE_N           = 78;  // N
static constexpr byte UPPERCASE_O           = 79;  // O
static constexpr byte UPPERCASE_P           = 80;  // P
static constexpr byte UPPERCASE_Q           = 81;  // Q
static constexpr byte UPPERCASE_R           = 82;  // R
static constexpr byte UPPERCASE_S           = 83;  // S
static constexpr byte UPPERCASE_T           = 84;  // T
static constexpr byte UPPERCASE_U           = 85;  // U
static constexpr byte UPPERCASE_V           = 86;  // V
static constexpr byte UPPERCASE_W           = 87;  // W
static constexpr byte UPPERCASE_X           = 88;  // X
static constexpr byte UPPERCASE_Y           = 89;  // Y
static constexpr byte UPPERCASE_Z           = 90;  // Z
static constexpr byte OPEN_BRACKET          = 91;  // [
static constexpr byte BACKSLASH             = 92;  // [\]
static constexpr byte CLOSE_BRACKET         = 93;  // ]
static constexpr byte CARET                 = 94;  // ^
static constexpr byte UNDERSCORE            = 95;  // _
static constexpr byte GRAVE                 = 96;  // `
static constexpr byte LOWERCASE_A           = 97;  // a
static constexpr byte LOWERCASE_B           = 98;  // b
static constexpr byte LOWERCASE_C           = 99;  // c
static constexpr byte LOWERCASE_D           = 100; // d
static constexpr byte LOWERCASE_E           = 101; // e
static constexpr byte LOWERCASE_F           = 102; // f
static constexpr byte LOWERCASE_G           = 103; // g
static constexpr byte LOWERCASE_H           = 104; // h
static constexpr byte LOWERCASE_I           = 105; // i
static constexpr byte LOWERCASE_J           = 106; // j
static constexpr byte LOWERCASE_K           = 107; // k
static constexpr byte LOWERCASE_L           = 108; // l
static constexpr byte LOWERCASE_M           = 109; // m
static constexpr byte LOWERCASE_N           = 110; // n
static constexpr byte LOWERCASE_O           = 111; // o
static constexpr byte LOWERCASE_P           = 112; // p
static constexpr byte LOWERCASE_Q           = 113; // q
static constexpr byte LOWERCASE_R           = 114; // r
static constexpr byte LOWERCASE_S           = 115; // s
static constexpr byte LOWERCASE_T           = 116; // t
static constexpr byte LOWERCASE_U           = 117; // u
static constexpr byte LOWERCASE_V           = 118; // v
static constexpr byte LOWERCASE_W           = 119; // w
static constexpr byte LOWERCASE_X           = 120; // x
static constexpr byte LOWERCASE_Y           = 121; // y
static constexpr byte LOWERCASE_Z           = 122; // z
static constexpr byte OPEN_BRACE            = 123; // {
static constexpr byte PIPE                  = 124; // |
static constexpr byte CLOSE_BRACE           = 125; // }
static constexpr byte TILDE                 = 126; // ~
static constexpr byte DEL                   = 127; // [DELETE]

}}}
