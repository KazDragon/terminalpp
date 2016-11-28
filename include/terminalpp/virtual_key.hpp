#pragma once

#include "terminalpp/ansi/control_sequence.hpp"
#include "terminalpp/detail/ascii.hpp"
#include <boost/variant.hpp>

namespace terminalpp {

enum class vk : u8
{
    bs                = terminalpp::detail::ascii::BS, // backspace
    ht                = terminalpp::detail::ascii::HT, // horizontal (forward) tabulation

    space             = terminalpp::detail::ascii::SPACE,
    exclamation_mark  = terminalpp::detail::ascii::EXCLAMATION_MARK,
    quotes            = terminalpp::detail::ascii::QUOTES,
    hash              = terminalpp::detail::ascii::HASH,
    dollar            = terminalpp::detail::ascii::DOLLAR,
    percent           = terminalpp::detail::ascii::PERCENT,
    ampersand         = terminalpp::detail::ascii::AMPERSAND,
    apostrophe        = terminalpp::detail::ascii::APOSTROPHE,
    open_parenthesis  = terminalpp::detail::ascii::OPEN_PARENTHESIS,
    close_parenthesis = terminalpp::detail::ascii::CLOSE_PARENTHESIS,
    asterisk          = terminalpp::detail::ascii::ASTERISK,
    plus              = terminalpp::detail::ascii::PLUS,
    comma             = terminalpp::detail::ascii::COMMA,
    dash              = terminalpp::detail::ascii::DASH,
    full_stop         = terminalpp::detail::ascii::FULL_STOP,
    slash             = terminalpp::detail::ascii::SLASH,
    zero              = terminalpp::detail::ascii::ZERO,
    one               = terminalpp::detail::ascii::ONE,
    two               = terminalpp::detail::ascii::TWO,
    three             = terminalpp::detail::ascii::THREE,
    four              = terminalpp::detail::ascii::FOUR,
    five              = terminalpp::detail::ascii::FIVE,
    six               = terminalpp::detail::ascii::SIX,
    seven             = terminalpp::detail::ascii::SEVEN,
    eight             = terminalpp::detail::ascii::EIGHT,
    nine              = terminalpp::detail::ascii::NINE,
    colon             = terminalpp::detail::ascii::COLON,
    semi_colon        = terminalpp::detail::ascii::SEMI_COLON,
    less_than         = terminalpp::detail::ascii::LESS_THAN,
    equals            = terminalpp::detail::ascii::EQUALS,
    greater_than      = terminalpp::detail::ascii::GREATER_THAN,
    question_mark     = terminalpp::detail::ascii::QUESTION_MARK,
    at                = terminalpp::detail::ascii::AT,

// Uppercase letters are considered to be entirely separate keypresses to
// lowercase letters. An alternative design might have been to consider a and
// A the same keypress with a shift modifier, but then it brings other things
// into question, such as what to do with '{'.  Is it always a shift-[?.  With
// that in mind, modifiers are reserved for keys that don't vary when pressing
// shift, e.g. Home, End, Arrow keys, F-keys and the like.
    uppercase_a       = terminalpp::detail::ascii::UPPERCASE_A,
    uppercase_b       = terminalpp::detail::ascii::UPPERCASE_B,
    uppercase_c       = terminalpp::detail::ascii::UPPERCASE_C,
    uppercase_d       = terminalpp::detail::ascii::UPPERCASE_D,
    uppercase_e       = terminalpp::detail::ascii::UPPERCASE_E,
    uppercase_f       = terminalpp::detail::ascii::UPPERCASE_F,
    uppercase_g       = terminalpp::detail::ascii::UPPERCASE_G,
    uppercase_h       = terminalpp::detail::ascii::UPPERCASE_H,
    uppercase_i       = terminalpp::detail::ascii::UPPERCASE_I,
    uppercase_j       = terminalpp::detail::ascii::UPPERCASE_J,
    uppercase_k       = terminalpp::detail::ascii::UPPERCASE_K,
    uppercase_l       = terminalpp::detail::ascii::UPPERCASE_L,
    uppercase_m       = terminalpp::detail::ascii::UPPERCASE_M,
    uppercase_n       = terminalpp::detail::ascii::UPPERCASE_N,
    uppercase_o       = terminalpp::detail::ascii::UPPERCASE_O,
    uppercase_p       = terminalpp::detail::ascii::UPPERCASE_P,
    uppercase_q       = terminalpp::detail::ascii::UPPERCASE_Q,
    uppercase_r       = terminalpp::detail::ascii::UPPERCASE_R,
    uppercase_s       = terminalpp::detail::ascii::UPPERCASE_S,
    uppercase_t       = terminalpp::detail::ascii::UPPERCASE_T,
    uppercase_u       = terminalpp::detail::ascii::UPPERCASE_U,
    uppercase_v       = terminalpp::detail::ascii::UPPERCASE_V,
    uppercase_w       = terminalpp::detail::ascii::UPPERCASE_W,
    uppercase_x       = terminalpp::detail::ascii::UPPERCASE_X,
    uppercase_y       = terminalpp::detail::ascii::UPPERCASE_Y,
    uppercase_z       = terminalpp::detail::ascii::UPPERCASE_Z,

    open_bracket      = terminalpp::detail::ascii::OPEN_BRACKET,
    backslash         = terminalpp::detail::ascii::BACKSLASH,
    close_bracket     = terminalpp::detail::ascii::CLOSE_BRACKET,
    caret             = terminalpp::detail::ascii::CARET,
    underscore        = terminalpp::detail::ascii::UNDERSCORE,
    grave             = terminalpp::detail::ascii::GRAVE,

    lowercase_a       = terminalpp::detail::ascii::LOWERCASE_A,
    lowercase_b       = terminalpp::detail::ascii::LOWERCASE_B,
    lowercase_c       = terminalpp::detail::ascii::LOWERCASE_C,
    lowercase_d       = terminalpp::detail::ascii::LOWERCASE_D,
    lowercase_e       = terminalpp::detail::ascii::LOWERCASE_E,
    lowercase_f       = terminalpp::detail::ascii::LOWERCASE_F,
    lowercase_g       = terminalpp::detail::ascii::LOWERCASE_G,
    lowercase_h       = terminalpp::detail::ascii::LOWERCASE_H,
    lowercase_i       = terminalpp::detail::ascii::LOWERCASE_I,
    lowercase_j       = terminalpp::detail::ascii::LOWERCASE_J,
    lowercase_k       = terminalpp::detail::ascii::LOWERCASE_K,
    lowercase_l       = terminalpp::detail::ascii::LOWERCASE_L,
    lowercase_m       = terminalpp::detail::ascii::LOWERCASE_M,
    lowercase_n       = terminalpp::detail::ascii::LOWERCASE_N,
    lowercase_o       = terminalpp::detail::ascii::LOWERCASE_O,
    lowercase_p       = terminalpp::detail::ascii::LOWERCASE_P,
    lowercase_q       = terminalpp::detail::ascii::LOWERCASE_Q,
    lowercase_r       = terminalpp::detail::ascii::LOWERCASE_R,
    lowercase_s       = terminalpp::detail::ascii::LOWERCASE_S,
    lowercase_t       = terminalpp::detail::ascii::LOWERCASE_T,
    lowercase_u       = terminalpp::detail::ascii::LOWERCASE_U,
    lowercase_v       = terminalpp::detail::ascii::LOWERCASE_V,
    lowercase_w       = terminalpp::detail::ascii::LOWERCASE_W,
    lowercase_x       = terminalpp::detail::ascii::LOWERCASE_X,
    lowercase_y       = terminalpp::detail::ascii::LOWERCASE_Y,
    lowercase_z       = terminalpp::detail::ascii::LOWERCASE_Z,

    open_brace        = terminalpp::detail::ascii::OPEN_BRACE,
    pipe              = terminalpp::detail::ascii::PIPE,
    close_brace       = terminalpp::detail::ascii::CLOSE_BRACE,
    tilde             = terminalpp::detail::ascii::TILDE,
    del               = terminalpp::detail::ascii::DEL,

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
