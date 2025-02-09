#pragma once

#include "terminalpp/core.hpp"
#include "terminalpp/detail/ascii.hpp"

namespace terminalpp::ansi {

// Note: For extended ASCII, both PuTTY and TeraTerm support SCO.
// clang-format off
inline constexpr byte charset_dec[]                  = {terminalpp::detail::ascii::zero};
inline constexpr byte charset_dec_supplementary[]    = {terminalpp::detail::ascii::less_than};
inline constexpr byte charset_dec_supplementary_gr[] = {terminalpp::detail::ascii::percent,
                                                        terminalpp::detail::ascii::five};
inline constexpr byte charset_dec_technical[]        = {terminalpp::detail::ascii::greater_than};
inline constexpr byte charset_uk[]                   = {terminalpp::detail::ascii::uppercase_a};
inline constexpr byte charset_us_ascii[]             = {terminalpp::detail::ascii::uppercase_b};
inline constexpr byte charset_dutch[]                = {terminalpp::detail::ascii::four};
inline constexpr byte charset_finnish[]              = {terminalpp::detail::ascii::uppercase_c};
inline constexpr byte charset_finnish_alt[]          = {terminalpp::detail::ascii::five};
inline constexpr byte charset_french[]               = {terminalpp::detail::ascii::uppercase_r};
inline constexpr byte charset_french_alt[]           = {terminalpp::detail::ascii::lowercase_f};
inline constexpr byte charset_french_canadian[]      = {terminalpp::detail::ascii::uppercase_q};
inline constexpr byte charset_french_canadian_alt[]  = {terminalpp::detail::ascii::nine};
inline constexpr byte charset_german[]               = {terminalpp::detail::ascii::uppercase_k};
inline constexpr byte charset_italian[]              = {terminalpp::detail::ascii::uppercase_y};
inline constexpr byte charset_danish[]               = {terminalpp::detail::ascii::grave};
inline constexpr byte charset_danish_alt_1[]         = {terminalpp::detail::ascii::uppercase_e};
inline constexpr byte charset_danish_alt_2[]         = {terminalpp::detail::ascii::six};
inline constexpr byte charset_portuguese[]           = {terminalpp::detail::ascii::percent,
                                                        terminalpp::detail::ascii::six};
inline constexpr byte charset_spanish[]              = {terminalpp::detail::ascii::uppercase_z};
inline constexpr byte charset_swedish[]              = {terminalpp::detail::ascii::uppercase_h};
inline constexpr byte charset_swedish_alt[]          = {terminalpp::detail::ascii::seven};
inline constexpr byte charset_swiss[]                = {terminalpp::detail::ascii::equals};
inline constexpr byte charset_sco[]                  = {terminalpp::detail::ascii::uppercase_u};

// Not defined by ANSI/VT100; just me bolting this on.
inline constexpr byte charset_utf8[]                 = {terminalpp::detail::ascii::lowercase_u};

// Some charsets (e.g. Portuguese) require an extender character
inline constexpr byte charset_extender               = terminalpp::detail::ascii::percent;

// Commands for Charset Selection
inline constexpr byte select_default_character_set[] = {terminalpp::detail::ascii::esc,
                                                        terminalpp::detail::ascii::percent,
                                                        terminalpp::detail::ascii::at};
inline constexpr byte select_utf8_character_set[]    = {terminalpp::detail::ascii::esc,
                                                        terminalpp::detail::ascii::percent,
                                                        terminalpp::detail::ascii::uppercase_g};
// Command openers for Designate G? Character Set commands.
inline constexpr byte set_charset_g0[]               = {terminalpp::detail::ascii::esc,
                                                        terminalpp::detail::ascii::open_parenthesis};
inline constexpr byte set_charset_g1[]               = {terminalpp::detail::ascii::esc,
                                                        terminalpp::detail::ascii::close_parenthesis};
inline constexpr byte set_charset_g2[]               = {terminalpp::detail::ascii::esc,
                                                        terminalpp::detail::ascii::asterisk};
inline constexpr byte set_charset_g3[]               = {terminalpp::detail::ascii::esc,
                                                        terminalpp::detail::ascii::plus};
inline constexpr byte set_charset_g1_alt[]           = {terminalpp::detail::ascii::esc,
                                                        terminalpp::detail::ascii::minus};
inline constexpr byte set_charset_g2_alt[]           = {terminalpp::detail::ascii::esc,
                                                        terminalpp::detail::ascii::full_stop};
inline constexpr byte set_charset_g3_alt[]           = {terminalpp::detail::ascii::esc,
                                                        terminalpp::detail::ascii::slash};
// clang-format on

}  // namespace terminalpp::ansi
