#pragma once

#include "terminalpp/detail/ascii.hpp"

namespace terminalpp { namespace ansi {

//* =========================================================================
/// \namespace terminalpp::ansi::control7
/// \brief Constants for 7-bit "C1" ANSI control sequences.
//* =========================================================================
namespace control7 {

// Full code for enabling 7-bit control mode.
static constexpr byte enable[] = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::space,
                                   terminalpp::detail::ascii::uppercase_f };

// The following codes are all prefixes for command groups.

// Index
static constexpr byte ind[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_d };
// Next Line
static constexpr byte nel[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_e };
// Horizontal Tab Set
static constexpr byte hts[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_h };
// Reverse Index
static constexpr byte ri[]     = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_m };
// Single Shift Select of G2 Charset (next character only)
static constexpr byte ss2[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_n };
// Single Shift Select of G3 Charset (next character only)
static constexpr byte ss3[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_o };
// Device Control String
static constexpr byte dcs[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_p };
// Start of Protected Area
static constexpr byte spa[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_v };
// End of Protected Area
static constexpr byte epa[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_w };
// Start of String
static constexpr byte sos[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_x };
// Return Terminal ID (obsolete)
static constexpr byte decid[]  = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_z };
// Control Sequence Introducer
static constexpr byte csi[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::open_bracket };
// String Terminator
static constexpr byte st[]     = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::backslash };
// Operating System Command
static constexpr byte osc[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::close_bracket };
// Privacy Message
static constexpr byte pm[]     = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::caret };
// Application Program Command
static constexpr byte apc[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::underscore };
}

//* =========================================================================
/// \namespace terminalpp::ansi::control8
/// \brief Constants for 8-bit "C1" ANSI control sequences.
//* =========================================================================
namespace control8 {

// Full command for enabling 8-bit control mode.
static constexpr byte enable[] = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::space,
                                   terminalpp::detail::ascii::uppercase_g };

// As above, the following codes are all prefixes for command groups.
// They have the same meaning, but a shorter representation.  However, only
// some terminals support them.

static constexpr byte ind[]   = { 0x84, 0x00 };
static constexpr byte nel[]   = { 0x85, 0x00 };
static constexpr byte hts[]   = { 0x88, 0x00 };
static constexpr byte ri[]    = { 0x8D, 0x00 };
static constexpr byte ss2[]   = { 0x8E, 0x00 };
static constexpr byte ss3[]   = { 0x8F, 0x00 };
static constexpr byte dcs[]   = { 0x90, 0x00 };
static constexpr byte spa[]   = { 0x96, 0x00 };
static constexpr byte epa[]   = { 0x97, 0x00 };
static constexpr byte sos[]   = { 0x98, 0x00 };
static constexpr byte decid[] = { 0x9A, 0x00 };
static constexpr byte csi[]   = { 0x9B, 0x00 };
static constexpr byte st[]    = { 0x9C, 0x00 };
static constexpr byte osc[]   = { 0x9D, 0x00 };
static constexpr byte pm[]    = { 0x9E, 0x00 };
static constexpr byte apc[]   = { 0x9F, 0x00 };

}

}}
