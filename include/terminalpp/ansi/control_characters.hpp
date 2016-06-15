#pragma once

#include "terminalpp/detail/ascii.hpp"

namespace terminalpp { namespace ansi {

//* =========================================================================
/// \namespace terminalpp::ansi::control7
/// \brief Constants for 7-bit "C1" ANSI control sequences.
//* =========================================================================
namespace control7 {

// Full code for enabling 7-bit control mode.
static constexpr char const ENABLE[]= { terminalpp::detail::ascii::ESC,
                                        terminalpp::detail::ascii::SPACE,
                                        terminalpp::detail::ascii::UPPERCASE_F, 0 };

// The following codes are all prefixes for command groups.

// Index
static constexpr char const IND[]   = { terminalpp::detail::ascii::ESC,
                                        terminalpp::detail::ascii::UPPERCASE_D, 0 };
// Next Line
static constexpr char const NEL[]   = { terminalpp::detail::ascii::ESC,
                                        terminalpp::detail::ascii::UPPERCASE_E, 0 };
// Horizontal Tab Set
static constexpr char const HTS[]   = { terminalpp::detail::ascii::ESC,
                                        terminalpp::detail::ascii::UPPERCASE_H, 0 };
// Reverse Index
static constexpr char const RI[]    = { terminalpp::detail::ascii::ESC,
                                        terminalpp::detail::ascii::UPPERCASE_M, 0 };
// Single Shift Select of G2 Charset (next character only)
static constexpr char const SS2[]   = { terminalpp::detail::ascii::ESC,
                                        terminalpp::detail::ascii::UPPERCASE_N, 0 };
// Single Shift Select of G3 Charset (next character only)
static constexpr char const SS3[]   = { terminalpp::detail::ascii::ESC,
                                        terminalpp::detail::ascii::UPPERCASE_O, 0 };
// Device Control String
static constexpr char const DCS[]   = { terminalpp::detail::ascii::ESC,
                                        terminalpp::detail::ascii::UPPERCASE_P, 0 };
// Start of Protected Area
static constexpr char const SPA[]   = { terminalpp::detail::ascii::ESC,
                                        terminalpp::detail::ascii::UPPERCASE_V, 0 };
// End of Protected Area
static constexpr char const EPA[]   = { terminalpp::detail::ascii::ESC,
                                        terminalpp::detail::ascii::UPPERCASE_W, 0 };
// Start of String
static constexpr char const SOS[]   = { terminalpp::detail::ascii::ESC,
                                        terminalpp::detail::ascii::UPPERCASE_X, 0 };
// Return Terminal ID (obsolete)
static constexpr char const DECID[] = { terminalpp::detail::ascii::ESC,
                                        terminalpp::detail::ascii::UPPERCASE_Z, 0 };
// Control Sequence Introducer
static constexpr char const CSI[]   = { terminalpp::detail::ascii::ESC,
                                        terminalpp::detail::ascii::OPEN_BRACKET, 0 };
// String Terminator
static constexpr char const ST[]    = { terminalpp::detail::ascii::ESC,
                                        terminalpp::detail::ascii::BACKSLASH, 0 };
// Operating System Command
static constexpr char const OSC[]   = { terminalpp::detail::ascii::ESC,
                                        terminalpp::detail::ascii::CLOSE_BRACKET, 0 };
// Privacy Message
static constexpr char const PM[]    = { terminalpp::detail::ascii::ESC,
                                        terminalpp::detail::ascii::CARET, 0 };
// Application Program Command
static constexpr char const APC[]   = { terminalpp::detail::ascii::ESC,
                                        terminalpp::detail::ascii::UNDERSCORE, 0 };
}

//* =========================================================================
/// \namespace terminalpp::ansi::control8
/// \brief Constants for 8-bit "C1" ANSI control sequences.
//* =========================================================================
namespace control8 {

// Full command for enabling 8-bit control mode.
static constexpr char const ENABLE[]= { terminalpp::detail::ascii::ESC,
                                        terminalpp::detail::ascii::SPACE,
                                        terminalpp::detail::ascii::UPPERCASE_G, 0 };

// As above, the following codes are all prefixes for command groups.
// They have the same meaning, but a shorter representation.  However, only
// some terminals support them.

static constexpr char const IND[]   = { char(0x84), 0x00 };
static constexpr char const NEL[]   = { char(0x85), 0x00 };
static constexpr char const HTS[]   = { char(0x88), 0x00 };
static constexpr char const RI[]    = { char(0x8D), 0x00 };
static constexpr char const SS2[]   = { char(0x8E), 0x00 };
static constexpr char const SS3[]   = { char(0x8F), 0x00 };
static constexpr char const DCS[]   = { char(0x90), 0x00 };
static constexpr char const SPA[]   = { char(0x96), 0x00 };
static constexpr char const EPA[]   = { char(0x97), 0x00 };
static constexpr char const SOS[]   = { char(0x98), 0x00 };
static constexpr char const DECID[] = { char(0x9A), 0x00 };
static constexpr char const CSI[]   = { char(0x9B), 0x00 };
static constexpr char const ST[]    = { char(0x9C), 0x00 };
static constexpr char const OSC[]   = { char(0x9D), 0x00 };
static constexpr char const PM[]    = { char(0x9E), 0x00 };
static constexpr char const APC[]   = { char(0x9F), 0x00 };

}

}}
