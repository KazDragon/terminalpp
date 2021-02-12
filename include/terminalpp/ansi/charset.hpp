#pragma once

#include "terminalpp/core.hpp"
#include "terminalpp/detail/ascii.hpp"
#include <boost/optional.hpp>
#include <string>

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
static constexpr byte CHARSET_DEC[]                 = {terminalpp::detail::ascii::ZERO};
static constexpr byte CHARSET_DEC_SUPPLEMENTARY[]   = {terminalpp::detail::ascii::LESS_THAN};
static constexpr byte CHARSET_DEC_SUPPLEMENTARY_GR[]= {terminalpp::detail::ascii::PERCENT,
                                                       terminalpp::detail::ascii::FIVE};
static constexpr byte CHARSET_DEC_TECHNICAL[]       = {terminalpp::detail::ascii::GREATER_THAN};
static constexpr byte CHARSET_UK[]                  = {terminalpp::detail::ascii::UPPERCASE_A};
static constexpr byte CHARSET_US_ASCII[]            = {terminalpp::detail::ascii::UPPERCASE_B};
static constexpr byte CHARSET_DUTCH[]               = {terminalpp::detail::ascii::FOUR};
static constexpr byte CHARSET_FINNISH[]             = {terminalpp::detail::ascii::UPPERCASE_C};
static constexpr byte CHARSET_FINNISH_ALT[]         = {terminalpp::detail::ascii::FIVE};
static constexpr byte CHARSET_FRENCH[]              = {terminalpp::detail::ascii::UPPERCASE_R};
static constexpr byte CHARSET_FRENCH_ALT[]          = {terminalpp::detail::ascii::LOWERCASE_F};
static constexpr byte CHARSET_FRENCH_CANADIAN[]     = {terminalpp::detail::ascii::UPPERCASE_Q};
static constexpr byte CHARSET_FRENCH_CANADIAN_ALT[] = {terminalpp::detail::ascii::NINE};
static constexpr byte CHARSET_GERMAN[]              = {terminalpp::detail::ascii::UPPERCASE_K};
static constexpr byte CHARSET_ITALIAN[]             = {terminalpp::detail::ascii::UPPERCASE_Y};
static constexpr byte CHARSET_DANISH[]              = {terminalpp::detail::ascii::GRAVE};
static constexpr byte CHARSET_DANISH_ALT_1[]        = {terminalpp::detail::ascii::UPPERCASE_E};
static constexpr byte CHARSET_DANISH_ALT_2[]        = {terminalpp::detail::ascii::SIX};
static constexpr byte CHARSET_PORTUGUESE[]          = {terminalpp::detail::ascii::PERCENT,
                                                       terminalpp::detail::ascii::SIX};
static constexpr byte CHARSET_SPANISH[]             = {terminalpp::detail::ascii::UPPERCASE_Z};
static constexpr byte CHARSET_SWEDISH[]             = {terminalpp::detail::ascii::UPPERCASE_H};
static constexpr byte CHARSET_SWEDISH_ALT[]         = {terminalpp::detail::ascii::SEVEN};
static constexpr byte CHARSET_SWISS[]               = {terminalpp::detail::ascii::EQUALS};
static constexpr byte CHARSET_SCO[]                 = {terminalpp::detail::ascii::UPPERCASE_U};

// Not defined by ANSI/VT100; just me bolting this on.
static constexpr byte CHARSET_UTF8[]                = {terminalpp::detail::ascii::LOWERCASE_U};

// Some charsets (e.g. Portuguese) require an extender character
static constexpr byte CHARSET_EXTENDER = terminalpp::detail::ascii::PERCENT;

// Commands for Charset Selection
static constexpr byte SELECT_DEFAULT_CHARACTER_SET[]= {terminalpp::detail::ascii::ESC,
                                                       terminalpp::detail::ascii::PERCENT,
                                                       terminalpp::detail::ascii::AT};
static constexpr byte SELECT_UTF8_CHARACTER_SET[]   = {terminalpp::detail::ascii::ESC,
                                                        terminalpp::detail::ascii::PERCENT,
                                                        terminalpp::detail::ascii::UPPERCASE_G};
// Command openers for Designate G? Character Set commands.
static constexpr byte SET_CHARSET_G0[]              = {terminalpp::detail::ascii::ESC,
                                                       terminalpp::detail::ascii::OPEN_PARENTHESIS};
static constexpr byte SET_CHARSET_G1[]              = {terminalpp::detail::ascii::ESC,
                                                       terminalpp::detail::ascii::CLOSE_PARENTHESIS};
static constexpr byte SET_CHARSET_G2[]              = {terminalpp::detail::ascii::ESC,
                                                       terminalpp::detail::ascii::ASTERISK};
static constexpr byte SET_CHARSET_G3[]              = {terminalpp::detail::ascii::ESC,
                                                       terminalpp::detail::ascii::PLUS};
static constexpr byte SET_CHARSET_G1_ALT[]          = {terminalpp::detail::ascii::ESC,
                                                       terminalpp::detail::ascii::MINUS};
static constexpr byte SET_CHARSET_G2_ALT[]          = {terminalpp::detail::ascii::ESC,
                                                       terminalpp::detail::ascii::FULL_STOP};
static constexpr byte SET_CHARSET_G3_ALT[]          = {terminalpp::detail::ascii::ESC,
                                                       terminalpp::detail::ascii::SLASH};

// Locale/Locale Code Conversion
//* =========================================================================
/// \brief Look up a character set by the ANSI code it uses.
/// E.g. lookup_charset("%6") yields charset::portuguese.
//* =========================================================================
TERMINALPP_EXPORT
boost::optional<charset> lookup_charset(bytes code);

}}
