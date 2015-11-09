#ifndef TERMINALPP_VIRTUAL_KEY_HPP_
#define TERMINALPP_VIRTUAL_KEY_HPP_

#include "terminalpp/ansi/control_sequence.hpp"
#include "terminalpp/detail/ascii.hpp"
#include <boost/variant.hpp>
#include <iosfwd>

namespace terminalpp {

// All keypresses for printable characters are represented using their ASCII
// values.

static constexpr char const VK_BS = ascii::BS;
static constexpr char const VK_HT = ascii::HT;
static constexpr char const VK_CR = ascii::CR;

static constexpr char const VK_SPACE = ascii::SPACE;

// TODO: ...
static constexpr char const VK_LOWERCASE_Z = ascii::LOWERCASE_Z;
static constexpr char const VK_UPPERCASE_Z = ascii::UPPERCASE_Z;

static constexpr char const VK_DEL = ascii::DEL;

/*
Now introduce constants for:
    function keys (1-24),
    home, pgup, pgdn,
    others?
*/

// TODO: Convert to an enum class.
static constexpr char const VK_UP    = VK_DEL  + 1;
static constexpr char const VK_DOWN  = VK_UP   + 1;
static constexpr char const VK_LEFT  = VK_DOWN + 1;
static constexpr char const VK_RIGHT = VK_LEFT + 1;

static constexpr char const VK_HOME  = VK_RIGHT + 1;
static constexpr char const VK_INS   = VK_HOME + 1;
static constexpr char const VK_END   = VK_INS  + 1;
static constexpr char const VK_PGUP  = VK_END  + 1;
static constexpr char const VK_PGDN  = VK_PGUP + 1;

static constexpr char const VK_F1    = VK_PGDN + 1;
static constexpr char const VK_F2    = VK_F1   + 1;
static constexpr char const VK_F3    = VK_F2   + 1;
static constexpr char const VK_F4    = VK_F3   + 1;
static constexpr char const VK_F5    = VK_F4   + 1;
static constexpr char const VK_F6    = VK_F5   + 1;
static constexpr char const VK_F7    = VK_F6   + 1;
static constexpr char const VK_F8    = VK_F7   + 1;
static constexpr char const VK_F9    = VK_F8   + 1;
static constexpr char const VK_F10   = VK_F9   + 1;
static constexpr char const VK_F11   = VK_F10  + 1;
static constexpr char const VK_F12   = VK_F11  + 1;
static constexpr char const VK_F13   = VK_F12  + 1;
static constexpr char const VK_F14   = VK_F13  + 1;
static constexpr char const VK_F15   = VK_F14  + 1;
static constexpr char const VK_F16   = VK_F15  + 1;
static constexpr char const VK_F17   = VK_F16  + 1;
static constexpr char const VK_F18   = VK_F17  + 1;
static constexpr char const VK_F19   = VK_F18  + 1;
static constexpr char const VK_F20   = VK_F19  + 1;
static constexpr char const VK_F21   = VK_F20  + 1;
static constexpr char const VK_F22   = VK_F21  + 1;
static constexpr char const VK_F23   = VK_F22  + 1;
static constexpr char const VK_F24   = VK_F23  + 1;

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

struct virtual_key
{
    /// \brief The actual key wer believe was pressed, selected from the
    /// list of VK constants.
    char key;

    /// \brief Any modifiers for the key, such as shift, ctrl, alt, meta,
    /// etc.
    char modifiers;

    /// \brief The repeat count of the character.
    char repeat_count;

    /// \brief The actual received data for the key.
    boost::variant<char, ansi::control_sequence> sequence;
};

bool operator==(virtual_key const &lhs, virtual_key const &rhs);

std::ostream &operator<<(std::ostream &out, virtual_key const &vk);

}

#endif