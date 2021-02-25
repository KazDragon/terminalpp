#pragma once

#include "terminalpp/detail/ascii.hpp"

namespace terminalpp { namespace ansi {

//* =========================================================================
/// \namespace terminalpp::ansi::control7
/// \brief Constants for 7-bit "C1" ANSI control sequences.
//* =========================================================================
namespace control7 {

// Full code for enabling 7-bit control mode.
static constexpr byte ENABLE[]= { terminalpp::detail::ascii::ESC,
                                  terminalpp::detail::ascii::SPACE,
                                  terminalpp::detail::ascii::UPPERCASE_F };

// The following codes are all prefixes for command groups.

// Index
static constexpr byte IND[]   = { terminalpp::detail::ascii::ESC,
                                  terminalpp::detail::ascii::UPPERCASE_D };
// Next Line
static constexpr byte NEL[]   = { terminalpp::detail::ascii::ESC,
                                  terminalpp::detail::ascii::UPPERCASE_E };
// Horizontal Tab Set
static constexpr byte HTS[]   = { terminalpp::detail::ascii::ESC,
                                  terminalpp::detail::ascii::UPPERCASE_H };
// Reverse Index
static constexpr byte RI[]    = { terminalpp::detail::ascii::ESC,
                                  terminalpp::detail::ascii::UPPERCASE_M };
// Single Shift Select of G2 Charset (next character only)
static constexpr byte SS2[]   = { terminalpp::detail::ascii::ESC,
                                  terminalpp::detail::ascii::UPPERCASE_N };
// Single Shift Select of G3 Charset (next character only)
static constexpr byte SS3[]   = { terminalpp::detail::ascii::ESC,
                                  terminalpp::detail::ascii::UPPERCASE_O };
// Device Control String
static constexpr byte DCS[]   = { terminalpp::detail::ascii::ESC,
                                  terminalpp::detail::ascii::UPPERCASE_P };
// Start of Protected Area
static constexpr byte SPA[]   = { terminalpp::detail::ascii::ESC,
                                  terminalpp::detail::ascii::UPPERCASE_V };
// End of Protected Area
static constexpr byte EPA[]   = { terminalpp::detail::ascii::ESC,
                                  terminalpp::detail::ascii::UPPERCASE_W };
// Start of String
static constexpr byte SOS[]   = { terminalpp::detail::ascii::ESC,
                                  terminalpp::detail::ascii::UPPERCASE_X };
// Return Terminal ID (obsolete)
static constexpr byte DECID[] = { terminalpp::detail::ascii::ESC,
                                  terminalpp::detail::ascii::UPPERCASE_Z };
// Control Sequence Introducer
static constexpr byte CSI[]   = { terminalpp::detail::ascii::ESC,
                                  terminalpp::detail::ascii::OPEN_BRACKET };
// String Terminator
static constexpr byte ST[]    = { terminalpp::detail::ascii::ESC,
                                  terminalpp::detail::ascii::BACKSLASH };
// Operating System Command
static constexpr byte OSC[]   = { terminalpp::detail::ascii::ESC,
                                  terminalpp::detail::ascii::CLOSE_BRACKET };
// Privacy Message
static constexpr byte PM[]    = { terminalpp::detail::ascii::ESC,
                                  terminalpp::detail::ascii::CARET };
// Application Program Command
static constexpr byte APC[]   = { terminalpp::detail::ascii::ESC,
                                  terminalpp::detail::ascii::UNDERSCORE };
}

//* =========================================================================
/// \namespace terminalpp::ansi::control8
/// \brief Constants for 8-bit "C1" ANSI control sequences.
//* =========================================================================
namespace control8 {

// Full command for enabling 8-bit control mode.
static constexpr byte ENABLE[]= { terminalpp::detail::ascii::ESC,
                                  terminalpp::detail::ascii::SPACE,
                                  terminalpp::detail::ascii::UPPERCASE_G };

// As above, the following codes are all prefixes for command groups.
// They have the same meaning, but a shorter representation.  However, only
// some terminals support them.

static constexpr byte IND[]   = { 0x84, 0x00 };
static constexpr byte NEL[]   = { 0x85, 0x00 };
static constexpr byte HTS[]   = { 0x88, 0x00 };
static constexpr byte RI[]    = { 0x8D, 0x00 };
static constexpr byte SS2[]   = { 0x8E, 0x00 };
static constexpr byte SS3[]   = { 0x8F, 0x00 };
static constexpr byte DCS[]   = { 0x90, 0x00 };
static constexpr byte SPA[]   = { 0x96, 0x00 };
static constexpr byte EPA[]   = { 0x97, 0x00 };
static constexpr byte SOS[]   = { 0x98, 0x00 };
static constexpr byte DECID[] = { 0x9A, 0x00 };
static constexpr byte CSI[]   = { 0x9B, 0x00 };
static constexpr byte ST[]    = { 0x9C, 0x00 };
static constexpr byte OSC[]   = { 0x9D, 0x00 };
static constexpr byte PM[]    = { 0x9E, 0x00 };
static constexpr byte APC[]   = { 0x9F, 0x00 };

}

}}
