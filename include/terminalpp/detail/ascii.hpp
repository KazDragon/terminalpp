#pragma once

//* =========================================================================
/// \namespace terminalpp::detail::ascii
/// \brief A namespace for constants representing the ASCII character set.
//* =========================================================================
namespace terminalpp { namespace detail { namespace ascii {

// Source: http://ascii-table.com/ascii.php

// Control Code Block
static char const NUL = 0;   // NULL
static char const STX = 1;   // Start Of Header
static char const SOT = 2;   // Start Of Text
static char const ETX = 3;   // End Of Text
static char const EOT = 4;   // End Of Transmission
static char const ENQ = 5;   // Enquiry
static char const ACK = 6;   // Acknowledge
static char const BEL = 7;   // Bell
static char const BS  = 8;   // Backspace
static char const HT  = 9;   // Horizontal Tabulation
static char const LF  = 10;  // Line Feed
static char const VT  = 11;  // Vertical Tabulation
static char const FF  = 12;  // Form Feed
static char const CR  = 13;  // Carriage Return
static char const SO  = 14;  // Shift Out
static char const SI  = 15;  // Shift In
static char const DLE = 16;  // Data Link Escape
static char const DC1 = 17;  // Device Control 1 (XON)
static char const DC2 = 18;  // Device Control 2
static char const DC3 = 19;  // Device Control 3 (XOFF)
static char const DC4 = 20;  // Device Control 4
static char const NAK = 21;  // Negative Acknowledge
static char const SYN = 22;  // Synchronous Idle
static char const ETB = 23;  // End Of Transmission Block
static char const CAN = 24;  // Cancel
static char const EM  = 25;  // End Of Medium
static char const SUB = 26;  // Substitute
static char const ESC = 27;  // Escape
static char const FS  = 28;  // File Separator
static char const GS  = 29;  // Group Separator
static char const RS  = 30;  // Record Separator
static char const US  = 31;  // Unit Separator

// Printable Character Block
static char const SPACE                 = 32;  // [SPACE]
static char const EXCLAMATION_MARK      = 33;  // !
static char const QUOTES                = 34;  // "
static char const HASH                  = 35;  // #
static char const DOLLAR                = 36;  // $
static char const PERCENT               = 37;  // %
static char const AMPERSAND             = 38;  // %
static char const APOSTROPHE            = 39;  // '
static char const OPEN_PARENTHESIS      = 40;  // (
static char const CLOSE_PARENTHESIS     = 41;  // )
static char const ASTERISK              = 42;  // *
static char const PLUS                  = 43;  // +
static char const COMMA                 = 44;  // ,
static char const DASH                  = 45;  // -
static char const FULL_STOP             = 46;  // .
static char const SLASH                 = 47;  // /
static char const ZERO                  = 48;  // 0
static char const ONE                   = 49;  // 1
static char const TWO                   = 50;  // 2
static char const THREE                 = 51;  // 3
static char const FOUR                  = 52;  // 4
static char const FIVE                  = 53;  // 5
static char const SIX                   = 54;  // 6
static char const SEVEN                 = 55;  // 7
static char const EIGHT                 = 56;  // 8
static char const NINE                  = 57;  // 9
static char const COLON                 = 58;  // :
static char const SEMI_COLON            = 59;  // ;
static char const LESS_THAN             = 60;  // <
static char const EQUALS                = 61;  // =
static char const GREATER_THAN          = 62;  // >
static char const QUESTION_MARK         = 63;  // ?
static char const AT                    = 64;  // @
static char const UPPERCASE_A           = 65;  // A
static char const UPPERCASE_B           = 66;  // B
static char const UPPERCASE_C           = 67;  // C
static char const UPPERCASE_D           = 68;  // D
static char const UPPERCASE_E           = 69;  // E
static char const UPPERCASE_F           = 70;  // F
static char const UPPERCASE_G           = 71;  // G
static char const UPPERCASE_H           = 72;  // H
static char const UPPERCASE_I           = 73;  // I
static char const UPPERCASE_J           = 74;  // J
static char const UPPERCASE_K           = 75;  // K
static char const UPPERCASE_L           = 76;  // L
static char const UPPERCASE_M           = 77;  // M
static char const UPPERCASE_N           = 78;  // N
static char const UPPERCASE_O           = 79;  // O
static char const UPPERCASE_P           = 80;  // P
static char const UPPERCASE_Q           = 81;  // Q
static char const UPPERCASE_R           = 82;  // R
static char const UPPERCASE_S           = 83;  // S
static char const UPPERCASE_T           = 84;  // T
static char const UPPERCASE_U           = 85;  // U
static char const UPPERCASE_V           = 86;  // V
static char const UPPERCASE_W           = 87;  // W
static char const UPPERCASE_X           = 88;  // X
static char const UPPERCASE_Y           = 89;  // Y
static char const UPPERCASE_Z           = 90;  // Z
static char const OPEN_BRACKET          = 91;  // [
static char const BACKSLASH             = 92;  // [\]
static char const CLOSE_BRACKET         = 93;  // ]
static char const CARET                 = 94;  // ^
static char const UNDERSCORE            = 95;  // _
static char const GRAVE                 = 96;  // `
static char const LOWERCASE_A           = 97;  // a
static char const LOWERCASE_B           = 98;  // b
static char const LOWERCASE_C           = 99;  // c
static char const LOWERCASE_D           = 100; // d
static char const LOWERCASE_E           = 101; // e
static char const LOWERCASE_F           = 102; // f
static char const LOWERCASE_G           = 103; // g
static char const LOWERCASE_H           = 104; // h
static char const LOWERCASE_I           = 105; // i
static char const LOWERCASE_J           = 106; // j
static char const LOWERCASE_K           = 107; // k
static char const LOWERCASE_L           = 108; // l
static char const LOWERCASE_M           = 109; // m
static char const LOWERCASE_N           = 110; // n
static char const LOWERCASE_O           = 111; // o
static char const LOWERCASE_P           = 112; // p
static char const LOWERCASE_Q           = 113; // q
static char const LOWERCASE_R           = 114; // r
static char const LOWERCASE_S           = 115; // s
static char const LOWERCASE_T           = 116; // t
static char const LOWERCASE_U           = 117; // u
static char const LOWERCASE_V           = 118; // v
static char const LOWERCASE_W           = 119; // w
static char const LOWERCASE_X           = 120; // x
static char const LOWERCASE_Y           = 121; // y
static char const LOWERCASE_Z           = 122; // z
static char const OPEN_BRACE            = 123; // {
static char const PIPE                  = 124; // |
static char const CLOSE_BRACE           = 125; // }
static char const TILDE                 = 126; // ~
static char const DEL                   = 127; // [DELETE]

}}}
