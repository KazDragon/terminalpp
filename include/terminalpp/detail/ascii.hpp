#pragma once
#include "terminalpp/core.hpp"

//* =========================================================================
/// \namespace terminalpp::detail::ascii
/// \brief A namespace for constants representing the ASCII character set.
//* =========================================================================
namespace terminalpp { namespace detail { namespace ascii {

// Source: http://ascii-table.com/ascii.php

// Control Code Block
static constexpr byte nul = 0;   // NULL
static constexpr byte soh = 1;   // Start Of Header
static constexpr byte stx = 2;   // Start Of Text
static constexpr byte etx = 3;   // End Of Text
static constexpr byte eot = 4;   // End Of Transmission
static constexpr byte enq = 5;   // Enquiry
static constexpr byte ack = 6;   // Acknowledge
static constexpr byte bel = 7;   // Bell
static constexpr byte bs  = 8;   // Backspace
static constexpr byte ht  = 9;   // Horizontal Tabulation
static constexpr byte lf  = 10;  // Line Feed
static constexpr byte vt  = 11;  // Vertical Tabulation
static constexpr byte ff  = 12;  // Form Feed
static constexpr byte cr  = 13;  // Carriage Return
static constexpr byte so  = 14;  // Shift Out
static constexpr byte si  = 15;  // Shift In
static constexpr byte dle = 16;  // Data Link Escape
static constexpr byte dc1 = 17;  // Device Control 1 (XON)
static constexpr byte dc2 = 18;  // Device Control 2
static constexpr byte dc3 = 19;  // Device Control 3 (XOFF)
static constexpr byte dc4 = 20;  // Device Control 4
static constexpr byte nak = 21;  // Negative Acknowledge
static constexpr byte syn = 22;  // Synchronous Idle
static constexpr byte etb = 23;  // End Of Transmission Block
static constexpr byte can = 24;  // Cancel
static constexpr byte em  = 25;  // End Of Medium
static constexpr byte sub = 26;  // Substitute
static constexpr byte esc = 27;  // Escape
static constexpr byte fs  = 28;  // File Separator
static constexpr byte gs  = 29;  // Group Separator
static constexpr byte rs  = 30;  // Record Separator
static constexpr byte us  = 31;  // Unit Separator

// Printable Character Block
static constexpr byte space                 = 32;  // [SPACE]
static constexpr byte exclamation_mark      = 33;  // !
static constexpr byte quotes                = 34;  // "
static constexpr byte hash                  = 35;  // #
static constexpr byte dollar                = 36;  // $
static constexpr byte percent               = 37;  // %
static constexpr byte ampersand             = 38;  // %
static constexpr byte apostrophe            = 39;  // '
static constexpr byte open_parenthesis      = 40;  // (
static constexpr byte close_parenthesis     = 41;  // )
static constexpr byte asterisk              = 42;  // *
static constexpr byte plus                  = 43;  // +
static constexpr byte comma                 = 44;  // ,
static constexpr byte minus                 = 45;  // -
static constexpr byte full_stop             = 46;  // .
static constexpr byte slash                 = 47;  // /
static constexpr byte zero                  = 48;  // 0
static constexpr byte one                   = 49;  // 1
static constexpr byte two                   = 50;  // 2
static constexpr byte three                 = 51;  // 3
static constexpr byte four                  = 52;  // 4
static constexpr byte five                  = 53;  // 5
static constexpr byte six                   = 54;  // 6
static constexpr byte seven                 = 55;  // 7
static constexpr byte eight                 = 56;  // 8
static constexpr byte nine                  = 57;  // 9
static constexpr byte colon                 = 58;  // :
static constexpr byte semi_colon            = 59;  // ;
static constexpr byte less_than             = 60;  // <
static constexpr byte equals                = 61;  // =
static constexpr byte greater_than          = 62;  // >
static constexpr byte question_mark         = 63;  // ?
static constexpr byte at                    = 64;  // @
static constexpr byte uppercase_a           = 65;  // A
static constexpr byte uppercase_b           = 66;  // B
static constexpr byte uppercase_c           = 67;  // C
static constexpr byte uppercase_d           = 68;  // D
static constexpr byte uppercase_e           = 69;  // E
static constexpr byte uppercase_f           = 70;  // F
static constexpr byte uppercase_g           = 71;  // G
static constexpr byte uppercase_h           = 72;  // H
static constexpr byte uppercase_i           = 73;  // I
static constexpr byte uppercase_j           = 74;  // J
static constexpr byte uppercase_k           = 75;  // K
static constexpr byte uppercase_l           = 76;  // L
static constexpr byte uppercase_m           = 77;  // M
static constexpr byte uppercase_n           = 78;  // N
static constexpr byte uppercase_o           = 79;  // O
static constexpr byte uppercase_p           = 80;  // P
static constexpr byte uppercase_q           = 81;  // Q
static constexpr byte uppercase_r           = 82;  // R
static constexpr byte uppercase_s           = 83;  // S
static constexpr byte uppercase_t           = 84;  // T
static constexpr byte uppercase_u           = 85;  // U
static constexpr byte uppercase_v           = 86;  // V
static constexpr byte uppercase_w           = 87;  // W
static constexpr byte uppercase_x           = 88;  // X
static constexpr byte uppercase_y           = 89;  // Y
static constexpr byte uppercase_z           = 90;  // Z
static constexpr byte open_bracket          = 91;  // [
static constexpr byte backslash             = 92;  // [\]
static constexpr byte close_bracket         = 93;  // ]
static constexpr byte caret                 = 94;  // ^
static constexpr byte underscore            = 95;  // _
static constexpr byte grave                 = 96;  // `
static constexpr byte lowercase_a           = 97;  // a
static constexpr byte lowercase_b           = 98;  // b
static constexpr byte lowercase_c           = 99;  // c
static constexpr byte lowercase_d           = 100; // d
static constexpr byte lowercase_e           = 101; // e
static constexpr byte lowercase_f           = 102; // f
static constexpr byte lowercase_g           = 103; // g
static constexpr byte lowercase_h           = 104; // h
static constexpr byte lowercase_i           = 105; // i
static constexpr byte lowercase_j           = 106; // j
static constexpr byte lowercase_k           = 107; // k
static constexpr byte lowercase_l           = 108; // l
static constexpr byte lowercase_m           = 109; // m
static constexpr byte lowercase_n           = 110; // n
static constexpr byte lowercase_o           = 111; // o
static constexpr byte lowercase_p           = 112; // p
static constexpr byte lowercase_q           = 113; // q
static constexpr byte lowercase_r           = 114; // r
static constexpr byte lowercase_s           = 115; // s
static constexpr byte lowercase_t           = 116; // t
static constexpr byte lowercase_u           = 117; // u
static constexpr byte lowercase_v           = 118; // v
static constexpr byte lowercase_w           = 119; // w
static constexpr byte lowercase_x           = 120; // x
static constexpr byte lowercase_y           = 121; // y
static constexpr byte lowercase_z           = 122; // z
static constexpr byte open_brace            = 123; // {
static constexpr byte pipe                  = 124; // |
static constexpr byte close_brace           = 125; // }
static constexpr byte tilde                 = 126; // ~
static constexpr byte del                   = 127; // [DELETE]

}}}
