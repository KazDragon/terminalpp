#ifndef TERMINALPP_ANSI_CONTROL_CHARACTERS_HPP_
#define TERMINALPP_ANSI_CONTROL_CHARACTERS_HPP_

#include "terminalpp/detail/ascii.hpp"

namespace terminalpp { namespace ansi {

// C1 7-Bit Control Sequences
namespace control7 {

// Index
static constexpr char const IND[]   = { terminalpp::ascii::ESC,
                                        terminalpp::ascii::UPPERCASE_D, 0};
// Next Line
static constexpr char const NEL[]   = { terminalpp::ascii::ESC,
                                        terminalpp::ascii::UPPERCASE_E, 0};
// Horizontal Tab Set
static constexpr char const HTS[]   = { terminalpp::ascii::ESC,
                                        terminalpp::ascii::UPPERCASE_H, 0};
// Reverse Index
static constexpr char const RI[]    = { terminalpp::ascii::ESC,
                                        terminalpp::ascii::UPPERCASE_M, 0};
// Single Shift Select of G2 Charset (next character only)
static constexpr char const SS2[]   = { terminalpp::ascii::ESC,
                                        terminalpp::ascii::UPPERCASE_N, 0};
// Single Shift Select of G3 Charset (next character only)
static constexpr char const SS3[]   = { terminalpp::ascii::ESC,
                                        terminalpp::ascii::UPPERCASE_O, 0};
// Device Control String
static constexpr char const DCS[]   = { terminalpp::ascii::ESC,
                                        terminalpp::ascii::UPPERCASE_P, 0};
// Start of Protected Area
static constexpr char const SPA[]   = { terminalpp::ascii::ESC,
                                        terminalpp::ascii::UPPERCASE_V, 0};
// End of Protected Area
static constexpr char const EPA[]   = { terminalpp::ascii::ESC,
                                        terminalpp::ascii::UPPERCASE_W, 0};
// Start of String
static constexpr char const SOS[]   = { terminalpp::ascii::ESC,
                                        terminalpp::ascii::UPPERCASE_X, 0};
// Return Terminal ID (obsolete)
static constexpr char const DECID[] = { terminalpp::ascii::ESC,
                                        terminalpp::ascii::UPPERCASE_Z, 0};
// Control Sequence Introducer
static constexpr char const CSI[]   = { terminalpp::ascii::ESC,
                                        terminalpp::ascii::OPEN_SQUARE_BRACKET, 0};
// String Terminator
static constexpr char const ST[]    = { terminalpp::ascii::ESC,
                                        terminalpp::ascii::BACKSLASH, 0};
// Operating System Command
static constexpr char const OSC[]   = { terminalpp::ascii::ESC,
                                        terminalpp::ascii::CLOSE_SQUARE_BRACKET, 0};
// Privacy Message
static constexpr char const PM[]    = { terminalpp::ascii::ESC,
                                        terminalpp::ascii::CARET, 0};
// Application Program Command
static constexpr char const APC[]   = { terminalpp::ascii::ESC,
                                        terminalpp::ascii::UNDERSCORE, 0};
}

// C1 8-Bit Control Sequences
namespace control8 {

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

#endif