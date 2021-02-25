#pragma once

#include "terminalpp/core.hpp"
#include "terminalpp/detail/ascii.hpp"

namespace terminalpp { namespace ansi {

// Note: For extended ASCII, both PuTTY and TeraTerm support SCO.
static constexpr byte charset_dec[]                  = {terminalpp::detail::ascii::zero};
static constexpr byte charset_dec_supplementary[]    = {terminalpp::detail::ascii::less_than};
static constexpr byte charset_dec_supplementary_gr[] = {terminalpp::detail::ascii::percent,
                                                        terminalpp::detail::ascii::five};
static constexpr byte charset_dec_technical[]        = {terminalpp::detail::ascii::greater_than};
static constexpr byte charset_uk[]                   = {terminalpp::detail::ascii::uppercase_a};
static constexpr byte charset_us_ascii[]             = {terminalpp::detail::ascii::uppercase_b};
static constexpr byte charset_dutch[]                = {terminalpp::detail::ascii::four};
static constexpr byte charset_finnish[]              = {terminalpp::detail::ascii::uppercase_c};
static constexpr byte charset_finnish_alt[]          = {terminalpp::detail::ascii::five};
static constexpr byte charset_french[]               = {terminalpp::detail::ascii::uppercase_r};
static constexpr byte charset_french_alt[]           = {terminalpp::detail::ascii::lowercase_f};
static constexpr byte charset_french_canadian[]      = {terminalpp::detail::ascii::uppercase_q};
static constexpr byte charset_french_canadian_alt[]  = {terminalpp::detail::ascii::nine};
static constexpr byte charset_german[]               = {terminalpp::detail::ascii::uppercase_k};
static constexpr byte charset_italian[]              = {terminalpp::detail::ascii::uppercase_y};
static constexpr byte charset_danish[]               = {terminalpp::detail::ascii::grave};
static constexpr byte charset_danish_alt_1[]         = {terminalpp::detail::ascii::uppercase_e};
static constexpr byte charset_danish_alt_2[]         = {terminalpp::detail::ascii::six};
static constexpr byte charset_portuguese[]           = {terminalpp::detail::ascii::percent,
                                                        terminalpp::detail::ascii::six};
static constexpr byte charset_spanish[]              = {terminalpp::detail::ascii::uppercase_z};
static constexpr byte charset_swedish[]              = {terminalpp::detail::ascii::uppercase_h};
static constexpr byte charset_swedish_alt[]          = {terminalpp::detail::ascii::seven};
static constexpr byte charset_swiss[]                = {terminalpp::detail::ascii::equals};
static constexpr byte charset_sco[]                  = {terminalpp::detail::ascii::uppercase_u};

// Not defined by ANSI/VT100; just me bolting this on.
static constexpr byte charset_utf8[]                 = {terminalpp::detail::ascii::lowercase_u};

// Some charsets (e.g. Portuguese) require an extender character
static constexpr byte charset_extender               = terminalpp::detail::ascii::percent;

// Commands for Charset Selection
static constexpr byte select_default_character_set[] = {terminalpp::detail::ascii::esc,
                                                        terminalpp::detail::ascii::percent,
                                                        terminalpp::detail::ascii::at};
static constexpr byte select_utf8_character_set[]    = {terminalpp::detail::ascii::esc,
                                                        terminalpp::detail::ascii::percent,
                                                        terminalpp::detail::ascii::uppercase_g};
// Command openers for Designate G? Character Set commands.
static constexpr byte set_charset_g0[]               = {terminalpp::detail::ascii::esc,
                                                        terminalpp::detail::ascii::open_parenthesis};
static constexpr byte set_charset_g1[]               = {terminalpp::detail::ascii::esc,
                                                        terminalpp::detail::ascii::close_parenthesis};
static constexpr byte set_charset_g2[]               = {terminalpp::detail::ascii::esc,
                                                        terminalpp::detail::ascii::asterisk};
static constexpr byte set_charset_g3[]               = {terminalpp::detail::ascii::esc,
                                                        terminalpp::detail::ascii::plus};
static constexpr byte set_charset_g1_alt[]           = {terminalpp::detail::ascii::esc,
                                                        terminalpp::detail::ascii::minus};
static constexpr byte set_charset_g2_alt[]           = {terminalpp::detail::ascii::esc,
                                                        terminalpp::detail::ascii::full_stop};
static constexpr byte set_charset_g3_alt[]           = {terminalpp::detail::ascii::esc,
                                                        terminalpp::detail::ascii::slash};
}}
