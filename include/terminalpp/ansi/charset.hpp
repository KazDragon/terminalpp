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
    danish,
    portuguese,
    spanish,
    swedish,
    swiss,
    sco,
    utf8,
};

// Note: For extended ASCII, both PuTTY and TeraTerm support SCO.
static constexpr char const CHARSET_DEC[]                 = {terminalpp::detail::ascii::ZERO, 0};
static constexpr char const CHARSET_DEC_SUPPLEMENTARY[]   = {terminalpp::detail::ascii::LESS_THAN, 0};
static constexpr char const CHARSET_DEC_SUPPLEMENTARY_GR[]= {terminalpp::detail::ascii::PERCENT,
                                                             terminalpp::detail::ascii::FIVE, 0};
static constexpr char const CHARSET_DEC_TECHNICAL[]       = {terminalpp::detail::ascii::GREATER_THAN, 0};
static constexpr char const CHARSET_UK[]                  = {terminalpp::detail::ascii::UPPERCASE_A, 0};
static constexpr char const CHARSET_US_ASCII[]            = {terminalpp::detail::ascii::UPPERCASE_B, 0};
static constexpr char const CHARSET_DUTCH[]               = {terminalpp::detail::ascii::FOUR, 0};
static constexpr char const CHARSET_FINNISH[]             = {terminalpp::detail::ascii::UPPERCASE_C, 0};
static constexpr char const CHARSET_FINNISH_ALT[]         = {terminalpp::detail::ascii::FIVE, 0};
static constexpr char const CHARSET_FRENCH[]              = {terminalpp::detail::ascii::UPPERCASE_R, 0};
static constexpr char const CHARSET_FRENCH_ALT[]          = {terminalpp::detail::ascii::LOWERCASE_F, 0};
static constexpr char const CHARSET_FRENCH_CANADIAN[]     = {terminalpp::detail::ascii::UPPERCASE_Q, 0};
static constexpr char const CHARSET_FRENCH_CANADIAN_ALT[] = {terminalpp::detail::ascii::NINE, 0};
static constexpr char const CHARSET_GERMAN[]              = {terminalpp::detail::ascii::UPPERCASE_K, 0};
static constexpr char const CHARSET_ITALIAN[]             = {terminalpp::detail::ascii::UPPERCASE_Y, 0};
static constexpr char const CHARSET_DANISH[]              = {terminalpp::detail::ascii::GRAVE, 0};
static constexpr char const CHARSET_DANISH_ALT_1[]        = {terminalpp::detail::ascii::UPPERCASE_E, 0};
static constexpr char const CHARSET_DANISH_ALT_2[]        = {terminalpp::detail::ascii::SIX, 0};
static constexpr char const CHARSET_PORTUGUESE[]          = {terminalpp::detail::ascii::PERCENT,
                                                             terminalpp::detail::ascii::SIX, 0};
static constexpr char const CHARSET_SPANISH[]             = {terminalpp::detail::ascii::UPPERCASE_Z, 0};
static constexpr char const CHARSET_SWEDISH[]             = {terminalpp::detail::ascii::UPPERCASE_H, 0};
static constexpr char const CHARSET_SWEDISH_ALT[]         = {terminalpp::detail::ascii::SEVEN, 0};
static constexpr char const CHARSET_SWISS[]               = {terminalpp::detail::ascii::EQUALS, 0};
static constexpr char const CHARSET_SCO[]                 = {terminalpp::detail::ascii::UPPERCASE_U, 0};

// Not defined by ANSI/VT100; just me bolting this on.
static constexpr char const CHARSET_UTF8[]                = {terminalpp::detail::ascii::LOWERCASE_U, 0};

// Some charsets (e.g. Portuguese) require an extender character
static constexpr char const CHARSET_EXTENDER = terminalpp::detail::ascii::PERCENT;

// Commands for Charset Selection
static constexpr char const SELECT_DEFAULT_CHARACTER_SET[]= {terminalpp::detail::ascii::ESC,
                                                             terminalpp::detail::ascii::PERCENT,
                                                             terminalpp::detail::ascii::AT, 0};
static constexpr char const SELECT_UTF8_CHARACTER_SET[]   = {terminalpp::detail::ascii::ESC,
                                                             terminalpp::detail::ascii::PERCENT,
                                                             terminalpp::detail::ascii::UPPERCASE_G, 0};
// Command openers for Designate G? Character Set commands.
static constexpr char const SET_CHARSET_G0[]              = {terminalpp::detail::ascii::ESC,
                                                             terminalpp::detail::ascii::OPEN_PARENTHESIS, 0};
static constexpr char const SET_CHARSET_G1[]              = {terminalpp::detail::ascii::ESC,
                                                             terminalpp::detail::ascii::CLOSE_PARENTHESIS, 0};
static constexpr char const SET_CHARSET_G2[]              = {terminalpp::detail::ascii::ESC,
                                                             terminalpp::detail::ascii::ASTERISK, 0};
static constexpr char const SET_CHARSET_G3[]              = {terminalpp::detail::ascii::ESC,
                                                             terminalpp::detail::ascii::PLUS, 0};
static constexpr char const SET_CHARSET_G1_ALT[]          = {terminalpp::detail::ascii::ESC,
                                                             terminalpp::detail::ascii::DASH, 0};
static constexpr char const SET_CHARSET_G2_ALT[]          = {terminalpp::detail::ascii::ESC,
                                                             terminalpp::detail::ascii::FULL_STOP, 0};
static constexpr char const SET_CHARSET_G3_ALT[]          = {terminalpp::detail::ascii::ESC,
                                                             terminalpp::detail::ascii::SLASH, 0};

// Locale/Locale Code Conversion
//* =========================================================================
/// \brief Look up a character set by the ANSI code it uses.
/// E.g. lookup_charset("%6") yields charset::portuguese.
//* =========================================================================
boost::optional<charset> lookup_charset(char const *code);

//* =========================================================================
/// \brief Convert a character set to its respective ANSI code.
/// E.g. charset_to_string(charset::portuguese) yields "%6".
//* =========================================================================
std::string charset_to_string(charset const &loc);

}}
