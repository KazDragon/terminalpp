#pragma once

#include "terminalpp/control_sequence.hpp"
#include "terminalpp/detail/ascii.hpp"
#include <boost/variant.hpp>
#include <iosfwd>

namespace terminalpp {

enum class vk : byte
{
    nul               = terminalpp::detail::ascii::nul,
    soh               = terminalpp::detail::ascii::soh,
    stx               = terminalpp::detail::ascii::stx,
    // ...
    bel               = terminalpp::detail::ascii::bel,
    bs                = terminalpp::detail::ascii::bs, // backspace
    ht                = terminalpp::detail::ascii::ht, // horizontal (forward) tabulation
    lf                = terminalpp::detail::ascii::lf,
    // ...
    cr                = terminalpp::detail::ascii::cr,
    // ...
    esc               = terminalpp::detail::ascii::esc,
    // ...
    space             = terminalpp::detail::ascii::space,
    exclamation_mark  = terminalpp::detail::ascii::exclamation_mark,
    quotes            = terminalpp::detail::ascii::quotes,
    hash              = terminalpp::detail::ascii::hash,
    dollar            = terminalpp::detail::ascii::dollar,
    percent           = terminalpp::detail::ascii::percent,
    ampersand         = terminalpp::detail::ascii::ampersand,
    apostrophe        = terminalpp::detail::ascii::apostrophe,
    open_parenthesis  = terminalpp::detail::ascii::open_parenthesis,
    close_parenthesis = terminalpp::detail::ascii::close_parenthesis,
    asterisk          = terminalpp::detail::ascii::asterisk,
    plus              = terminalpp::detail::ascii::plus,
    comma             = terminalpp::detail::ascii::comma,
    minus             = terminalpp::detail::ascii::minus,
    full_stop         = terminalpp::detail::ascii::full_stop,
    slash             = terminalpp::detail::ascii::slash,
    zero              = terminalpp::detail::ascii::zero,
    one               = terminalpp::detail::ascii::one,
    two               = terminalpp::detail::ascii::two,
    three             = terminalpp::detail::ascii::three,
    four              = terminalpp::detail::ascii::four,
    five              = terminalpp::detail::ascii::five,
    six               = terminalpp::detail::ascii::six,
    seven             = terminalpp::detail::ascii::seven,
    eight             = terminalpp::detail::ascii::eight,
    nine              = terminalpp::detail::ascii::nine,
    colon             = terminalpp::detail::ascii::colon,
    semi_colon        = terminalpp::detail::ascii::semi_colon,
    less_than         = terminalpp::detail::ascii::less_than,
    equals            = terminalpp::detail::ascii::equals,
    greater_than      = terminalpp::detail::ascii::greater_than,
    question_mark     = terminalpp::detail::ascii::question_mark,
    at                = terminalpp::detail::ascii::at,

// Uppercase letters are considered to be entirely separate keypresses to
// lowercase letters. An alternative design might have been to consider a and
// A the same keypress with a shift modifier, but then it brings other things
// into question, such as what to do with '{'.  Is it always a shift-[?.  With
// that in mind, modifiers are reserved for keys that don't vary when pressing
// shift, e.g. Home, End, Arrow keys, F-keys and the like.
    uppercase_a       = terminalpp::detail::ascii::uppercase_a,
    uppercase_b       = terminalpp::detail::ascii::uppercase_b,
    uppercase_c       = terminalpp::detail::ascii::uppercase_c,
    uppercase_d       = terminalpp::detail::ascii::uppercase_d,
    uppercase_e       = terminalpp::detail::ascii::uppercase_e,
    uppercase_f       = terminalpp::detail::ascii::uppercase_f,
    uppercase_g       = terminalpp::detail::ascii::uppercase_g,
    uppercase_h       = terminalpp::detail::ascii::uppercase_h,
    uppercase_i       = terminalpp::detail::ascii::uppercase_i,
    uppercase_j       = terminalpp::detail::ascii::uppercase_j,
    uppercase_k       = terminalpp::detail::ascii::uppercase_k,
    uppercase_l       = terminalpp::detail::ascii::uppercase_l,
    uppercase_m       = terminalpp::detail::ascii::uppercase_m,
    uppercase_n       = terminalpp::detail::ascii::uppercase_n,
    uppercase_o       = terminalpp::detail::ascii::uppercase_o,
    uppercase_p       = terminalpp::detail::ascii::uppercase_p,
    uppercase_q       = terminalpp::detail::ascii::uppercase_q,
    uppercase_r       = terminalpp::detail::ascii::uppercase_r,
    uppercase_s       = terminalpp::detail::ascii::uppercase_s,
    uppercase_t       = terminalpp::detail::ascii::uppercase_t,
    uppercase_u       = terminalpp::detail::ascii::uppercase_u,
    uppercase_v       = terminalpp::detail::ascii::uppercase_v,
    uppercase_w       = terminalpp::detail::ascii::uppercase_w,
    uppercase_x       = terminalpp::detail::ascii::uppercase_x,
    uppercase_y       = terminalpp::detail::ascii::uppercase_y,
    uppercase_z       = terminalpp::detail::ascii::uppercase_z,

    open_bracket      = terminalpp::detail::ascii::open_bracket,
    backslash         = terminalpp::detail::ascii::backslash,
    close_bracket     = terminalpp::detail::ascii::close_bracket,
    caret             = terminalpp::detail::ascii::caret,
    underscore        = terminalpp::detail::ascii::underscore,
    grave             = terminalpp::detail::ascii::grave,

    lowercase_a       = terminalpp::detail::ascii::lowercase_a,
    lowercase_b       = terminalpp::detail::ascii::lowercase_b,
    lowercase_c       = terminalpp::detail::ascii::lowercase_c,
    lowercase_d       = terminalpp::detail::ascii::lowercase_d,
    lowercase_e       = terminalpp::detail::ascii::lowercase_e,
    lowercase_f       = terminalpp::detail::ascii::lowercase_f,
    lowercase_g       = terminalpp::detail::ascii::lowercase_g,
    lowercase_h       = terminalpp::detail::ascii::lowercase_h,
    lowercase_i       = terminalpp::detail::ascii::lowercase_i,
    lowercase_j       = terminalpp::detail::ascii::lowercase_j,
    lowercase_k       = terminalpp::detail::ascii::lowercase_k,
    lowercase_l       = terminalpp::detail::ascii::lowercase_l,
    lowercase_m       = terminalpp::detail::ascii::lowercase_m,
    lowercase_n       = terminalpp::detail::ascii::lowercase_n,
    lowercase_o       = terminalpp::detail::ascii::lowercase_o,
    lowercase_p       = terminalpp::detail::ascii::lowercase_p,
    lowercase_q       = terminalpp::detail::ascii::lowercase_q,
    lowercase_r       = terminalpp::detail::ascii::lowercase_r,
    lowercase_s       = terminalpp::detail::ascii::lowercase_s,
    lowercase_t       = terminalpp::detail::ascii::lowercase_t,
    lowercase_u       = terminalpp::detail::ascii::lowercase_u,
    lowercase_v       = terminalpp::detail::ascii::lowercase_v,
    lowercase_w       = terminalpp::detail::ascii::lowercase_w,
    lowercase_x       = terminalpp::detail::ascii::lowercase_x,
    lowercase_y       = terminalpp::detail::ascii::lowercase_y,
    lowercase_z       = terminalpp::detail::ascii::lowercase_z,

    open_brace        = terminalpp::detail::ascii::open_brace,
    pipe              = terminalpp::detail::ascii::pipe,
    close_brace       = terminalpp::detail::ascii::close_brace,
    tilde             = terminalpp::detail::ascii::tilde,
    del               = terminalpp::detail::ascii::del,

    // At this point, we have gone from values 0x00-0x7F.  That is, the 7-byte
    // ASCII set.  Anything between these values is deliberately convertible to
    // the char value.  Beyond this point, these are all abstract keys, and NOT
    // actual character values.
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

enum class vk_modifier : byte
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
    using input_sequence = boost::variant<byte, control_sequence>;

    /// \brief The actual key we believe was pressed, selected from the
    /// list of VK constants.
    vk key = vk::nul;

    /// \brief Any modifiers for the key, such as shift, ctrl, alt, meta,
    /// etc.
    vk_modifier modifiers = vk_modifier::none;

    /// \brief The repeat count of the character.
    int repeat_count = 0;

    /// \brief The actual received data for the key.
    input_sequence sequence;
};

//* =========================================================================
/// \brief Equality operator for virtual_keys.
//* =========================================================================
TERMINALPP_EXPORT
bool operator==(virtual_key const &lhs, virtual_key const &rhs);

//* =========================================================================
/// \brief Streaming output operator
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, virtual_key const &vk);

//* =========================================================================
/// \brief Allow the or-ing of virtual key modifiers.
//* =========================================================================
constexpr vk_modifier operator|(vk_modifier const &lhs, vk_modifier const &rhs)
{
    return vk_modifier(byte(lhs) | byte(rhs));
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
    return vk_modifier(byte(lhs) & byte(rhs));
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
