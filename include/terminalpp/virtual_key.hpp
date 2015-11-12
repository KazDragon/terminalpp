#ifndef TERMINALPP_VIRTUAL_KEY_HPP_
#define TERMINALPP_VIRTUAL_KEY_HPP_

#include "terminalpp/ansi/control_sequence.hpp"
#include "terminalpp/detail/ascii.hpp"
#include <boost/variant.hpp>
#include <iosfwd>

namespace terminalpp {

enum class vk : u8
{
    bs = ascii::BS,
    ht = ascii::HT,
    cr = ascii::CR,

    space = ascii::SPACE,

    // TODO: ...
    lowercase_a = ascii::LOWERCASE_A,
    lowercase_b = ascii::LOWERCASE_B,
    lowercase_c = ascii::LOWERCASE_C,
    lowercase_d = ascii::LOWERCASE_D,
    lowercase_e = ascii::LOWERCASE_E,
    lowercase_f = ascii::LOWERCASE_F,
    lowercase_g = ascii::LOWERCASE_G,
    lowercase_h = ascii::LOWERCASE_H,
    lowercase_i = ascii::LOWERCASE_I,
    lowercase_j = ascii::LOWERCASE_J,
    lowercase_k = ascii::LOWERCASE_K,
    lowercase_l = ascii::LOWERCASE_L,
    lowercase_m = ascii::LOWERCASE_M,
    lowercase_n = ascii::LOWERCASE_N,
    lowercase_o = ascii::LOWERCASE_O,
    lowercase_p = ascii::LOWERCASE_P,
    lowercase_q = ascii::LOWERCASE_Q,
    lowercase_r = ascii::LOWERCASE_R,
    lowercase_s = ascii::LOWERCASE_S,
    lowercase_t = ascii::LOWERCASE_T,
    lowercase_u = ascii::LOWERCASE_U,
    lowercase_v = ascii::LOWERCASE_V,
    lowercase_w = ascii::LOWERCASE_W,
    lowercase_x = ascii::LOWERCASE_X,
    lowercase_y = ascii::LOWERCASE_Y,
    lowercase_z = ascii::LOWERCASE_Z,

// Uppercase letters are considered to be entirely separate keypresses. An
// alternative design might have been to consider a and A the same keypress
// with a shift modifier, but then it brings other things into question, such
// as what to do with '{'.  Is it always a shift-[?.  With that in mind,
// modifiers are reserved for keys that don't vary when pressing shift:
// Home, End, Arrow keys, F-keys and the like.
    uppercase_a = ascii::UPPERCASE_A,
    uppercase_b = ascii::UPPERCASE_B,
    uppercase_c = ascii::UPPERCASE_C,
    uppercase_d = ascii::UPPERCASE_D,
    uppercase_e = ascii::UPPERCASE_E,
    uppercase_f = ascii::UPPERCASE_F,
    uppercase_g = ascii::UPPERCASE_G,
    uppercase_h = ascii::UPPERCASE_H,
    uppercase_i = ascii::UPPERCASE_I,
    uppercase_j = ascii::UPPERCASE_J,
    uppercase_k = ascii::UPPERCASE_K,
    uppercase_l = ascii::UPPERCASE_L,
    uppercase_m = ascii::UPPERCASE_M,
    uppercase_n = ascii::UPPERCASE_N,
    uppercase_o = ascii::UPPERCASE_O,
    uppercase_p = ascii::UPPERCASE_P,
    uppercase_q = ascii::UPPERCASE_Q,
    uppercase_r = ascii::UPPERCASE_R,
    uppercase_s = ascii::UPPERCASE_S,
    uppercase_t = ascii::UPPERCASE_T,
    uppercase_u = ascii::UPPERCASE_U,
    uppercase_v = ascii::UPPERCASE_V,
    uppercase_w = ascii::UPPERCASE_W,
    uppercase_x = ascii::UPPERCASE_X,
    uppercase_y = ascii::UPPERCASE_Y,
    uppercase_z = ascii::UPPERCASE_Z,

    del = ascii::DEL,

    // TODO: Convert to an enum class.
    cursor_up,
    cursor_down,
    cursor_left,
    cursor_right,

    home,
    ins,
    end,
    pgup,
    pgdn,

    f1,
    f2,
    f3,
    f4,
    f5,
    f6,
    f7,
    f8,
    f9,
    f10,
    f11,
    f12,

/*
static char const SPACE                 = 32;  // [SPACE]
static char const EXLAMATION_MARK       = 33;  // !
static char const QUOTES                = 34;  // "
static char const HASH                  = 35;  // #
static char const DOLLAR                = 36;  // $
static char const PERCENT               = 37;  // %
static char const AMPERSAND             = 38;  // %
static char const APOSTROPHE            = 39;  // '
static char const OPEN_BRACKET          = 40;  // (
static char const CLOSE_BRACKET         = 41;  // )
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
static char const OPEN_SQUARE_BRACKET   = 91;  // [
static char const BACKSLASH             = 92;  // [\]
static char const CLOSE_SQUARE_BRACKET  = 93;  // ]
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
*/
};

enum class vk_modifier : u8
{
    none = 0,
    shift = (1 << 0),
    ctrl  = (1 << 1),
    alt   = (1 << 2),
    meta  = (1 << 3),
};

struct virtual_key
{
    /// \brief The actual key we believe was pressed, selected from the
    /// list of VK constants.
    vk key;

    /// \brief Any modifiers for the key, such as shift, ctrl, alt, meta,
    /// etc.
    vk_modifier modifiers;

    /// \brief The repeat count of the character.
    char repeat_count;

    /// \brief The actual received data for the key.
    boost::variant<char, ansi::control_sequence> sequence;
};

bool operator==(virtual_key const &lhs, virtual_key const &rhs);

std::ostream &operator<<(std::ostream &out, virtual_key const &vk);

constexpr vk_modifier operator|(vk_modifier const &lhs, vk_modifier const &rhs)
{
    return vk_modifier(u8(lhs) | u8(rhs));
}

}

#endif