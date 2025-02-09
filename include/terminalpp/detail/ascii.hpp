#pragma once
#include "terminalpp/core.hpp"

//* =========================================================================
/// \namespace terminalpp::detail::ascii
/// \brief A namespace for constants representing the ASCII character set.
//* =========================================================================
namespace terminalpp::detail::ascii {

// Source: http://ascii-table.com/ascii.php

// clang-format off
// Control Code Block
inline constexpr byte nul = 0;   // NULL
inline constexpr byte soh = 1;   // Start Of Header
inline constexpr byte stx = 2;   // Start Of Text
inline constexpr byte etx = 3;   // End Of Text
inline constexpr byte eot = 4;   // End Of Transmission
inline constexpr byte enq = 5;   // Enquiry
inline constexpr byte ack = 6;   // Acknowledge
inline constexpr byte bel = 7;   // Bell
inline constexpr byte bs  = 8;   // Backspace
inline constexpr byte ht  = 9;   // Horizontal Tabulation
inline constexpr byte lf  = 10;  // Line Feed
inline constexpr byte vt  = 11;  // Vertical Tabulation
inline constexpr byte ff  = 12;  // Form Feed
inline constexpr byte cr  = 13;  // Carriage Return
inline constexpr byte so  = 14;  // Shift Out
inline constexpr byte si  = 15;  // Shift In
inline constexpr byte dle = 16;  // Data Link Escape
inline constexpr byte dc1 = 17;  // Device Control 1 (XON)
inline constexpr byte dc2 = 18;  // Device Control 2
inline constexpr byte dc3 = 19;  // Device Control 3 (XOFF)
inline constexpr byte dc4 = 20;  // Device Control 4
inline constexpr byte nak = 21;  // Negative Acknowledge
inline constexpr byte syn = 22;  // Synchronous Idle
inline constexpr byte etb = 23;  // End Of Transmission Block
inline constexpr byte can = 24;  // Cancel
inline constexpr byte em  = 25;  // End Of Medium
inline constexpr byte sub = 26;  // Substitute
inline constexpr byte esc = 27;  // Escape
inline constexpr byte fs  = 28;  // File Separator
inline constexpr byte gs  = 29;  // Group Separator
inline constexpr byte rs  = 30;  // Record Separator
inline constexpr byte us  = 31;  // Unit Separator

// Printable Character Block
inline constexpr byte space                 = 32;  // [SPACE]
inline constexpr byte exclamation_mark      = 33;  // !
inline constexpr byte quotes                = 34;  // "
inline constexpr byte hash                  = 35;  // #
inline constexpr byte dollar                = 36;  // $
inline constexpr byte percent               = 37;  // %
inline constexpr byte ampersand             = 38;  // %
inline constexpr byte apostrophe            = 39;  // '
inline constexpr byte open_parenthesis      = 40;  // (
inline constexpr byte close_parenthesis     = 41;  // )
inline constexpr byte asterisk              = 42;  // *
inline constexpr byte plus                  = 43;  // +
inline constexpr byte comma                 = 44;  // ,
inline constexpr byte minus                 = 45;  // -
inline constexpr byte full_stop             = 46;  // .
inline constexpr byte slash                 = 47;  // /
inline constexpr byte zero                  = 48;  // 0
inline constexpr byte one                   = 49;  // 1
inline constexpr byte two                   = 50;  // 2
inline constexpr byte three                 = 51;  // 3
inline constexpr byte four                  = 52;  // 4
inline constexpr byte five                  = 53;  // 5
inline constexpr byte six                   = 54;  // 6
inline constexpr byte seven                 = 55;  // 7
inline constexpr byte eight                 = 56;  // 8
inline constexpr byte nine                  = 57;  // 9
inline constexpr byte colon                 = 58;  // :
inline constexpr byte semi_colon            = 59;  // ;
inline constexpr byte less_than             = 60;  // <
inline constexpr byte equals                = 61;  // =
inline constexpr byte greater_than          = 62;  // >
inline constexpr byte question_mark         = 63;  // ?
inline constexpr byte at                    = 64;  // @
inline constexpr byte uppercase_a           = 65;  // A
inline constexpr byte uppercase_b           = 66;  // B
inline constexpr byte uppercase_c           = 67;  // C
inline constexpr byte uppercase_d           = 68;  // D
inline constexpr byte uppercase_e           = 69;  // E
inline constexpr byte uppercase_f           = 70;  // F
inline constexpr byte uppercase_g           = 71;  // G
inline constexpr byte uppercase_h           = 72;  // H
inline constexpr byte uppercase_i           = 73;  // I
inline constexpr byte uppercase_j           = 74;  // J
inline constexpr byte uppercase_k           = 75;  // K
inline constexpr byte uppercase_l           = 76;  // L
inline constexpr byte uppercase_m           = 77;  // M
inline constexpr byte uppercase_n           = 78;  // N
inline constexpr byte uppercase_o           = 79;  // O
inline constexpr byte uppercase_p           = 80;  // P
inline constexpr byte uppercase_q           = 81;  // Q
inline constexpr byte uppercase_r           = 82;  // R
inline constexpr byte uppercase_s           = 83;  // S
inline constexpr byte uppercase_t           = 84;  // T
inline constexpr byte uppercase_u           = 85;  // U
inline constexpr byte uppercase_v           = 86;  // V
inline constexpr byte uppercase_w           = 87;  // W
inline constexpr byte uppercase_x           = 88;  // X
inline constexpr byte uppercase_y           = 89;  // Y
inline constexpr byte uppercase_z           = 90;  // Z
inline constexpr byte open_bracket          = 91;  // [
inline constexpr byte backslash             = 92;  // [\]
inline constexpr byte close_bracket         = 93;  // ]
inline constexpr byte caret                 = 94;  // ^
inline constexpr byte underscore            = 95;  // _
inline constexpr byte grave                 = 96;  // `
inline constexpr byte lowercase_a           = 97;  // a
inline constexpr byte lowercase_b           = 98;  // b
inline constexpr byte lowercase_c           = 99;  // c
inline constexpr byte lowercase_d           = 100; // d
inline constexpr byte lowercase_e           = 101; // e
inline constexpr byte lowercase_f           = 102; // f
inline constexpr byte lowercase_g           = 103; // g
inline constexpr byte lowercase_h           = 104; // h
inline constexpr byte lowercase_i           = 105; // i
inline constexpr byte lowercase_j           = 106; // j
inline constexpr byte lowercase_k           = 107; // k
inline constexpr byte lowercase_l           = 108; // l
inline constexpr byte lowercase_m           = 109; // m
inline constexpr byte lowercase_n           = 110; // n
inline constexpr byte lowercase_o           = 111; // o
inline constexpr byte lowercase_p           = 112; // p
inline constexpr byte lowercase_q           = 113; // q
inline constexpr byte lowercase_r           = 114; // r
inline constexpr byte lowercase_s           = 115; // s
inline constexpr byte lowercase_t           = 116; // t
inline constexpr byte lowercase_u           = 117; // u
inline constexpr byte lowercase_v           = 118; // v
inline constexpr byte lowercase_w           = 119; // w
inline constexpr byte lowercase_x           = 120; // x
inline constexpr byte lowercase_y           = 121; // y
inline constexpr byte lowercase_z           = 122; // z
inline constexpr byte open_brace            = 123; // {
inline constexpr byte pipe                  = 124; // |
inline constexpr byte close_brace           = 125; // }
inline constexpr byte tilde                 = 126; // ~
inline constexpr byte del                   = 127; // [DELETE]
// clang-format on

}  // namespace terminalpp::detail::ascii
