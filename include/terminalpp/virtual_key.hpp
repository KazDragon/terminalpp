#pragma once

#include "terminalpp/ansi/control_sequence.hpp"
#include "terminalpp/detail/ascii.hpp"
#include <boost/variant.hpp>
#include <iosfwd>

namespace terminalpp {

enum class vk : u8
{
    bs                = ascii::BS, // backspace
    ht                = ascii::HT, // horizontal (forward) tabulation

    space             = ascii::SPACE,
    exclamation_mark  = ascii::EXCLAMATION_MARK,
    quotes            = ascii::QUOTES,
    hash              = ascii::HASH,
    dollar            = ascii::DOLLAR,
    percent           = ascii::PERCENT,
    ampersand         = ascii::AMPERSAND,
    apostrophe        = ascii::APOSTROPHE,
    open_parenthesis  = ascii::OPEN_PARENTHESIS,
    close_parenthesis = ascii::CLOSE_PARENTHESIS,
    asterisk          = ascii::ASTERISK,
    plus              = ascii::PLUS,
    comma             = ascii::COMMA,
    dash              = ascii::DASH,
    full_stop         = ascii::FULL_STOP,
    slash             = ascii::SLASH,
    zero              = ascii::ZERO,
    one               = ascii::ONE,
    two               = ascii::TWO,
    three             = ascii::THREE,
    four              = ascii::FOUR,
    five              = ascii::FIVE,
    six               = ascii::SIX,
    seven             = ascii::SEVEN,
    eight             = ascii::EIGHT,
    nine              = ascii::NINE,
    colon             = ascii::COLON,
    semi_colon        = ascii::SEMI_COLON,
    less_than         = ascii::LESS_THAN,
    equals            = ascii::EQUALS,
    greater_than      = ascii::GREATER_THAN,
    question_mark     = ascii::QUESTION_MARK,
    at                = ascii::AT,

// Uppercase letters are considered to be entirely separate keypresses to
// lowercase letters. An alternative design might have been to consider a and
// A the same keypress with a shift modifier, but then it brings other things
// into question, such as what to do with '{'.  Is it always a shift-[?.  With
// that in mind, modifiers are reserved for keys that don't vary when pressing
// shift, e.g. Home, End, Arrow keys, F-keys and the like.
    uppercase_a       = ascii::UPPERCASE_A,
    uppercase_b       = ascii::UPPERCASE_B,
    uppercase_c       = ascii::UPPERCASE_C,
    uppercase_d       = ascii::UPPERCASE_D,
    uppercase_e       = ascii::UPPERCASE_E,
    uppercase_f       = ascii::UPPERCASE_F,
    uppercase_g       = ascii::UPPERCASE_G,
    uppercase_h       = ascii::UPPERCASE_H,
    uppercase_i       = ascii::UPPERCASE_I,
    uppercase_j       = ascii::UPPERCASE_J,
    uppercase_k       = ascii::UPPERCASE_K,
    uppercase_l       = ascii::UPPERCASE_L,
    uppercase_m       = ascii::UPPERCASE_M,
    uppercase_n       = ascii::UPPERCASE_N,
    uppercase_o       = ascii::UPPERCASE_O,
    uppercase_p       = ascii::UPPERCASE_P,
    uppercase_q       = ascii::UPPERCASE_Q,
    uppercase_r       = ascii::UPPERCASE_R,
    uppercase_s       = ascii::UPPERCASE_S,
    uppercase_t       = ascii::UPPERCASE_T,
    uppercase_u       = ascii::UPPERCASE_U,
    uppercase_v       = ascii::UPPERCASE_V,
    uppercase_w       = ascii::UPPERCASE_W,
    uppercase_x       = ascii::UPPERCASE_X,
    uppercase_y       = ascii::UPPERCASE_Y,
    uppercase_z       = ascii::UPPERCASE_Z,

    open_bracket      = ascii::OPEN_BRACKET,
    backslash         = ascii::BACKSLASH,
    close_bracket     = ascii::CLOSE_BRACKET,
    caret             = ascii::CARET,
    underscore        = ascii::UNDERSCORE,
    grave             = ascii::GRAVE,

    lowercase_a       = ascii::LOWERCASE_A,
    lowercase_b       = ascii::LOWERCASE_B,
    lowercase_c       = ascii::LOWERCASE_C,
    lowercase_d       = ascii::LOWERCASE_D,
    lowercase_e       = ascii::LOWERCASE_E,
    lowercase_f       = ascii::LOWERCASE_F,
    lowercase_g       = ascii::LOWERCASE_G,
    lowercase_h       = ascii::LOWERCASE_H,
    lowercase_i       = ascii::LOWERCASE_I,
    lowercase_j       = ascii::LOWERCASE_J,
    lowercase_k       = ascii::LOWERCASE_K,
    lowercase_l       = ascii::LOWERCASE_L,
    lowercase_m       = ascii::LOWERCASE_M,
    lowercase_n       = ascii::LOWERCASE_N,
    lowercase_o       = ascii::LOWERCASE_O,
    lowercase_p       = ascii::LOWERCASE_P,
    lowercase_q       = ascii::LOWERCASE_Q,
    lowercase_r       = ascii::LOWERCASE_R,
    lowercase_s       = ascii::LOWERCASE_S,
    lowercase_t       = ascii::LOWERCASE_T,
    lowercase_u       = ascii::LOWERCASE_U,
    lowercase_v       = ascii::LOWERCASE_V,
    lowercase_w       = ascii::LOWERCASE_W,
    lowercase_x       = ascii::LOWERCASE_X,
    lowercase_y       = ascii::LOWERCASE_Y,
    lowercase_z       = ascii::LOWERCASE_Z,

    open_brace        = ascii::OPEN_BRACE,
    pipe              = ascii::PIPE,
    close_brace       = ascii::CLOSE_BRACE,
    tilde             = ascii::TILDE,
    del               = ascii::DEL,

    cursor_up,
    cursor_down,
    cursor_left,
    cursor_right,

    home,
    ins,
    end,
    pgup,
    pgdn,

    bt, // backward tabulation
    enter,

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

};

enum class vk_modifier : u8
{
    none  = 0,
    shift = (1 << 0),
    ctrl  = (1 << 1),
    alt   = (1 << 2),
    meta  = (1 << 3),
};

//* =========================================================================
/// \brief A class that represents a keypress, possibly combined with
/// modifiers such as shift, ctrl, etc.
//* =========================================================================
struct TERMINALPP_EXPORT virtual_key
{
    /// \brief The actual key we believe was pressed, selected from the
    /// list of VK constants.
    vk key;

    /// \brief Any modifiers for the key, such as shift, ctrl, alt, meta,
    /// etc.
    vk_modifier modifiers;

    /// \brief The repeat count of the character.
    u32 repeat_count;

    /// \brief The actual received data for the key.
    boost::variant<char, ansi::control_sequence> sequence;
};

//* =========================================================================
/// \brief Equality operator for virtual_keys.
//* =========================================================================
TERMINALPP_EXPORT
bool operator==(virtual_key const &lhs, virtual_key const &rhs);

//* =========================================================================
/// \brief Stream operator for virtual_keys.
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, virtual_key const &vk);

//* =========================================================================
/// \brief Allow the or-ing of virtual key modifiers.
//* =========================================================================
constexpr vk_modifier operator|(vk_modifier const &lhs, vk_modifier const &rhs)
{
    return vk_modifier(u8(lhs) | u8(rhs));
}

//* =========================================================================
/// \brief Or-assignment of virtual key modifiers.
//* =========================================================================
constexpr vk_modifier &operator|=(vk_modifier &lhs, vk_modifier const &rhs)
{
    lhs = lhs | rhs;
    return lhs;
}

//* =========================================================================
/// \brief Allow the and-ing of virtual key modifiers.
//* =========================================================================
constexpr vk_modifier operator&(vk_modifier const &lhs, vk_modifier const &rhs)
{
    return vk_modifier(u8(lhs) & u8(rhs));
}

//* =========================================================================
/// \brief And-assignment of virtual key modifiers.
//* =========================================================================
constexpr vk_modifier &operator&=(vk_modifier &lhs, vk_modifier const &rhs)
{
    lhs = lhs & rhs;
    return lhs;
}

}
