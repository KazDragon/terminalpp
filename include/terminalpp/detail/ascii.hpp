#pragma once

//* =========================================================================
/// \namespace terminalpp::detail::ascii
/// \brief A namespace for constants representing the ASCII character set.
//* =========================================================================
namespace terminalpp { namespace detail { namespace ascii {

// Source: http://ascii-table.com/ascii.php

// Control Code Block
static constexpr char const NUL = 0;   // NULL
static constexpr char const STX = 1;   // Start Of Header
static constexpr char const SOT = 2;   // Start Of Text
static constexpr char const ETX = 3;   // End Of Text
static constexpr char const EOT = 4;   // End Of Transmission
static constexpr char const ENQ = 5;   // Enquiry
static constexpr char const ACK = 6;   // Acknowledge
static constexpr char const BEL = 7;   // Bell
static constexpr char const BS  = 8;   // Backspace
static constexpr char const HT  = 9;   // Horizontal Tabulation
static constexpr char const LF  = 10;  // Line Feed
static constexpr char const VT  = 11;  // Vertical Tabulation
static constexpr char const FF  = 12;  // Form Feed
static constexpr char const CR  = 13;  // Carriage Return
static constexpr char const SO  = 14;  // Shift Out
static constexpr char const SI  = 15;  // Shift In
static constexpr char const DLE = 16;  // Data Link Escape
static constexpr char const DC1 = 17;  // Device Control 1 (XON)
static constexpr char const DC2 = 18;  // Device Control 2
static constexpr char const DC3 = 19;  // Device Control 3 (XOFF)
static constexpr char const DC4 = 20;  // Device Control 4
static constexpr char const NAK = 21;  // Negative Acknowledge
static constexpr char const SYN = 22;  // Synchronous Idle
static constexpr char const ETB = 23;  // End Of Transmission Block
static constexpr char const CAN = 24;  // Cancel
static constexpr char const EM  = 25;  // End Of Medium
static constexpr char const SUB = 26;  // Substitute
static constexpr char const ESC = 27;  // Escape
static constexpr char const FS  = 28;  // File Separator
static constexpr char const GS  = 29;  // Group Separator
static constexpr char const RS  = 30;  // Record Separator
static constexpr char const US  = 31;  // Unit Separator

// Printable Character Block
static constexpr char const SPACE                 = 32;  // [SPACE]
static constexpr char const EXCLAMATION_MARK      = 33;  // !
static constexpr char const QUOTES                = 34;  // "
static constexpr char const HASH                  = 35;  // #
static constexpr char const DOLLAR                = 36;  // $
static constexpr char const PERCENT               = 37;  // %
static constexpr char const AMPERSAND             = 38;  // %
static constexpr char const APOSTROPHE            = 39;  // '
static constexpr char const OPEN_PARENTHESIS      = 40;  // (
static constexpr char const CLOSE_PARENTHESIS     = 41;  // )
static constexpr char const ASTERISK              = 42;  // *
static constexpr char const PLUS                  = 43;  // +
static constexpr char const COMMA                 = 44;  // ,
static constexpr char const DASH                  = 45;  // -
static constexpr char const FULL_STOP             = 46;  // .
static constexpr char const SLASH                 = 47;  // /
static constexpr char const ZERO                  = 48;  // 0
static constexpr char const ONE                   = 49;  // 1
static constexpr char const TWO                   = 50;  // 2
static constexpr char const THREE                 = 51;  // 3
static constexpr char const FOUR                  = 52;  // 4
static constexpr char const FIVE                  = 53;  // 5
static constexpr char const SIX                   = 54;  // 6
static constexpr char const SEVEN                 = 55;  // 7
static constexpr char const EIGHT                 = 56;  // 8
static constexpr char const NINE                  = 57;  // 9
static constexpr char const COLON                 = 58;  // :
static constexpr char const SEMI_COLON            = 59;  // ;
static constexpr char const LESS_THAN             = 60;  // <
static constexpr char const EQUALS                = 61;  // =
static constexpr char const GREATER_THAN          = 62;  // >
static constexpr char const QUESTION_MARK         = 63;  // ?
static constexpr char const AT                    = 64;  // @
static constexpr char const UPPERCASE_A           = 65;  // A
static constexpr char const UPPERCASE_B           = 66;  // B
static constexpr char const UPPERCASE_C           = 67;  // C
static constexpr char const UPPERCASE_D           = 68;  // D
static constexpr char const UPPERCASE_E           = 69;  // E
static constexpr char const UPPERCASE_F           = 70;  // F
static constexpr char const UPPERCASE_G           = 71;  // G
static constexpr char const UPPERCASE_H           = 72;  // H
static constexpr char const UPPERCASE_I           = 73;  // I
static constexpr char const UPPERCASE_J           = 74;  // J
static constexpr char const UPPERCASE_K           = 75;  // K
static constexpr char const UPPERCASE_L           = 76;  // L
static constexpr char const UPPERCASE_M           = 77;  // M
static constexpr char const UPPERCASE_N           = 78;  // N
static constexpr char const UPPERCASE_O           = 79;  // O
static constexpr char const UPPERCASE_P           = 80;  // P
static constexpr char const UPPERCASE_Q           = 81;  // Q
static constexpr char const UPPERCASE_R           = 82;  // R
static constexpr char const UPPERCASE_S           = 83;  // S
static constexpr char const UPPERCASE_T           = 84;  // T
static constexpr char const UPPERCASE_U           = 85;  // U
static constexpr char const UPPERCASE_V           = 86;  // V
static constexpr char const UPPERCASE_W           = 87;  // W
static constexpr char const UPPERCASE_X           = 88;  // X
static constexpr char const UPPERCASE_Y           = 89;  // Y
static constexpr char const UPPERCASE_Z           = 90;  // Z
static constexpr char const OPEN_BRACKET          = 91;  // [
static constexpr char const BACKSLASH             = 92;  // [\]
static constexpr char const CLOSE_BRACKET         = 93;  // ]
static constexpr char const CARET                 = 94;  // ^
static constexpr char const UNDERSCORE            = 95;  // _
static constexpr char const GRAVE                 = 96;  // `
static constexpr char const LOWERCASE_A           = 97;  // a
static constexpr char const LOWERCASE_B           = 98;  // b
static constexpr char const LOWERCASE_C           = 99;  // c
static constexpr char const LOWERCASE_D           = 100; // d
static constexpr char const LOWERCASE_E           = 101; // e
static constexpr char const LOWERCASE_F           = 102; // f
static constexpr char const LOWERCASE_G           = 103; // g
static constexpr char const LOWERCASE_H           = 104; // h
static constexpr char const LOWERCASE_I           = 105; // i
static constexpr char const LOWERCASE_J           = 106; // j
static constexpr char const LOWERCASE_K           = 107; // k
static constexpr char const LOWERCASE_L           = 108; // l
static constexpr char const LOWERCASE_M           = 109; // m
static constexpr char const LOWERCASE_N           = 110; // n
static constexpr char const LOWERCASE_O           = 111; // o
static constexpr char const LOWERCASE_P           = 112; // p
static constexpr char const LOWERCASE_Q           = 113; // q
static constexpr char const LOWERCASE_R           = 114; // r
static constexpr char const LOWERCASE_S           = 115; // s
static constexpr char const LOWERCASE_T           = 116; // t
static constexpr char const LOWERCASE_U           = 117; // u
static constexpr char const LOWERCASE_V           = 118; // v
static constexpr char const LOWERCASE_W           = 119; // w
static constexpr char const LOWERCASE_X           = 120; // x
static constexpr char const LOWERCASE_Y           = 121; // y
static constexpr char const LOWERCASE_Z           = 122; // z
static constexpr char const OPEN_BRACE            = 123; // {
static constexpr char const PIPE                  = 124; // |
static constexpr char const CLOSE_BRACE           = 125; // }
static constexpr char const TILDE                 = 126; // ~
static constexpr char const DEL                   = 127; // [DELETE]

}}}
