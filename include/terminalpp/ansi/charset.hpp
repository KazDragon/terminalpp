#pragma once

#include "terminalpp/detail/ascii.hpp"
#include <boost/optional.hpp>

namespace terminalpp { namespace ansi {

enum class charset : char {
    dec,
    dec_supplementary,
    dec_supplementary_graphics,
    dec_technical,
    uk,
    us_ascii,
    dutch,
    finnish,
    french,
    french_canadian,
    german,
    italian,
    norwegian,
    danish,
    portuguese,
    spanish,
    swedish,
    swiss,
    sco,
    utf8,
};

// Note: For extended ASCII, both PuTTY and TeraTerm support SCO.
static constexpr char const CHARSET_DEC[]                 = {terminalpp::ascii::ZERO, 0};
static constexpr char const CHARSET_DEC_SUPPLEMENTARY[]   = {terminalpp::ascii::LESS_THAN, 0};
static constexpr char const CHARSET_DEC_SUPPLEMENTARY_GR[]= {terminalpp::ascii::PERCENT,
                                                             terminalpp::ascii::FIVE, 0};
static constexpr char const CHARSET_DEC_TECHNICAL[]       = {terminalpp::ascii::GREATER_THAN, 0};
static constexpr char const CHARSET_UK[]                  = {terminalpp::ascii::UPPERCASE_A, 0};
static constexpr char const CHARSET_US_ASCII[]            = {terminalpp::ascii::UPPERCASE_B, 0};
static constexpr char const CHARSET_DUTCH[]               = {terminalpp::ascii::FOUR, 0};
static constexpr char const CHARSET_FINNISH[]             = {terminalpp::ascii::UPPERCASE_C, 0};
static constexpr char const CHARSET_FINNISH_ALT[]         = {terminalpp::ascii::FIVE, 0};
static constexpr char const CHARSET_FRENCH[]              = {terminalpp::ascii::UPPERCASE_R, 0};
static constexpr char const CHARSET_FRENCH_ALT[]          = {terminalpp::ascii::LOWERCASE_F, 0};
static constexpr char const CHARSET_FRENCH_CANADIAN[]     = {terminalpp::ascii::UPPERCASE_Q, 0};
static constexpr char const CHARSET_FRENCH_CANADIAN_ALT[] = {terminalpp::ascii::NINE, 0};
static constexpr char const CHARSET_GERMAN[]              = {terminalpp::ascii::UPPERCASE_K, 0};
static constexpr char const CHARSET_ITALIAN[]             = {terminalpp::ascii::UPPERCASE_Y, 0};
static constexpr char const CHARSET_NORWEGIAN[]           = {terminalpp::ascii::GRAVE, 0};
static constexpr char const CHARSET_NORWEGIAN_ALT_1[]     = {terminalpp::ascii::UPPERCASE_E, 0};
static constexpr char const CHARSET_NORWEGIAN_ALT_2[]     = {terminalpp::ascii::SIX, 0};
static constexpr char const CHARSET_DANISH[]              = {terminalpp::ascii::GRAVE, 0};
static constexpr char const CHARSET_DANISH_ALT_1[]        = {terminalpp::ascii::UPPERCASE_E, 0};
static constexpr char const CHARSET_DANISH_ALT_2[]        = {terminalpp::ascii::SIX, 0};
static constexpr char const CHARSET_PORTUGUESE[]          = {terminalpp::ascii::PERCENT,
                                                             terminalpp::ascii::SIX, 0};
static constexpr char const CHARSET_SPANISH[]             = {terminalpp::ascii::UPPERCASE_Z, 0};
static constexpr char const CHARSET_SWEDISH[]             = {terminalpp::ascii::UPPERCASE_H, 0};
static constexpr char const CHARSET_SWEDISH_ALT[]         = {terminalpp::ascii::SEVEN, 0};
static constexpr char const CHARSET_SWISS[]               = {terminalpp::ascii::EQUALS, 0};
static constexpr char const CHARSET_SCO[]                 = {terminalpp::ascii::UPPERCASE_U, 0};

// Not defined by ANSI/VT100; just me bolting this on.
static constexpr char const CHARSET_UTF8[]                = {terminalpp::ascii::LOWERCASE_U, 0};

// Commands for Charset Selection
static constexpr char const SELECT_DEFAULT_CHARACTER_SET[]= {terminalpp::ascii::ESC,
                                                             terminalpp::ascii::PERCENT,
                                                             terminalpp::ascii::AT, 0};
static constexpr char const SELECT_UTF8_CHARACTER_SET[]   = {terminalpp::ascii::ESC,
                                                             terminalpp::ascii::PERCENT,
                                                             terminalpp::ascii::UPPERCASE_G, 0};
// Command openers for Designate G? Character Set commands.
static constexpr char const SET_CHARSET_G0[]              = {terminalpp::ascii::ESC,
                                                             terminalpp::ascii::OPEN_PARENTHESIS, 0};
static constexpr char const SET_CHARSET_G1[]              = {terminalpp::ascii::ESC,
                                                             terminalpp::ascii::CLOSE_PARENTHESIS, 0};
static constexpr char const SET_CHARSET_G2[]              = {terminalpp::ascii::ESC,
                                                             terminalpp::ascii::ASTERISK, 0};
static constexpr char const SET_CHARSET_G3[]              = {terminalpp::ascii::ESC,
                                                             terminalpp::ascii::PLUS, 0};
static constexpr char const SET_CHARSET_G1_ALT[]          = {terminalpp::ascii::ESC,
                                                             terminalpp::ascii::DASH, 0};
static constexpr char const SET_CHARSET_G2_ALT[]          = {terminalpp::ascii::ESC,
                                                             terminalpp::ascii::FULL_STOP, 0};
static constexpr char const SET_CHARSET_G3_ALT[]          = {terminalpp::ascii::ESC,
                                                             terminalpp::ascii::SLASH, 0};

// Locale/Locale Code Conversion
boost::optional<charset> lookup_charset(char const *code);
std::string charset_to_string(charset const &loc);

}}
