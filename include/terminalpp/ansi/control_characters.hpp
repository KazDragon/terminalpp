#pragma once

#include "terminalpp/detail/ascii.hpp"

namespace terminalpp::ansi {

//* =========================================================================
/// \namespace terminalpp::ansi::control7
/// \brief Constants for 7-bit "C1" ANSI control sequences.
//* =========================================================================
namespace control7 {

// clang-format off
// Full code for enabling 7-bit control mode.
inline constexpr byte enable[] = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::space,
                                   terminalpp::detail::ascii::uppercase_f };

// The following codes are all prefixes for command groups.

// Index
inline constexpr byte ind[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_d };
// Next Line
inline constexpr byte nel[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_e };
// Horizontal Tab Set
inline constexpr byte hts[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_h };
// Reverse Index
inline constexpr byte ri[]     = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_m };
// Single Shift Select of G2 Charset (next character only)
inline constexpr byte ss2[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_n };
// Single Shift Select of G3 Charset (next character only)
inline constexpr byte ss3[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_o };
// Device Control String
inline constexpr byte dcs[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_p };
// Start of Protected Area
inline constexpr byte spa[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_v };
// End of Protected Area
inline constexpr byte epa[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_w };
// Start of String
inline constexpr byte sos[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_x };
// Return Terminal ID (obsolete)
inline constexpr byte decid[]  = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::uppercase_z };
// Control Sequence Introducer
inline constexpr byte csi[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::open_bracket };
// String Terminator
inline constexpr byte st[]     = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::backslash };
// Operating System Command
inline constexpr byte osc[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::close_bracket };
// Privacy Message
inline constexpr byte pm[]     = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::caret };
// Application Program Command
inline constexpr byte apc[]    = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::underscore };
}  // namespace control7

//* =========================================================================
/// \namespace terminalpp::ansi::control8
/// \brief Constants for 8-bit "C1" ANSI control sequences.
//* =========================================================================
namespace control8 {

// Full command for enabling 8-bit control mode.
inline constexpr byte enable[] = { terminalpp::detail::ascii::esc,
                                   terminalpp::detail::ascii::space,
                                   terminalpp::detail::ascii::uppercase_g };

// As above, the following codes are all prefixes for command groups.
// They have the same meaning, but a shorter representation.  However, only
// some terminals support them.

inline constexpr byte ind   = 0x84;
inline constexpr byte nel   = 0x85;
inline constexpr byte hts   = 0x88;
inline constexpr byte ri    = 0x8D;
inline constexpr byte ss2   = 0x8E;
inline constexpr byte ss3   = 0x8F;
inline constexpr byte dcs   = 0x90;
inline constexpr byte spa   = 0x96;
inline constexpr byte epa   = 0x97;
inline constexpr byte sos   = 0x98;
inline constexpr byte decid = 0x9A;
inline constexpr byte csi   = 0x9B;
inline constexpr byte st    = 0x9C;
inline constexpr byte osc   = 0x9D;
inline constexpr byte pm    = 0x9E;
inline constexpr byte apc   = 0x9F;
// clang-format off

}  // namespace control8
}  // namespace terminalpp::ansi
