#pragma once

#include "terminalpp/detail/ascii.hpp"

namespace terminalpp { namespace ansi {

// Sequence for introducing DEC Private Mode
static constexpr byte DEC_PRIVATE_MODE[] = { terminalpp::detail::ascii::QUESTION_MARK, 0 };

//* =========================================================================
/// \namespace terminalpp::ansi::dec_pm
/// \brief Contains all of the constants for the commands that begin with the
/// DEC Private Mode sequence.
//* =========================================================================
namespace dec_pm {

static constexpr byte SET[]    = { terminalpp::detail::ascii::LOWERCASE_H, 0 };
static constexpr byte RESET[]  = { terminalpp::detail::ascii::LOWERCASE_L, 0 };

// Set = cursor visible; Reset = cursor hidden
static constexpr byte CURSOR[] = { terminalpp::detail::ascii::TWO,
                                   terminalpp::detail::ascii::FIVE, 0 };

// Set = use basic mouse tracking.  Reset =  stop using basic mouse tracking.
static constexpr byte BASIC_MOUSE_TRACKING[] =
                                  { terminalpp::detail::ascii::ONE,
                                    terminalpp::detail::ascii::ZERO,
                                    terminalpp::detail::ascii::ZERO,
                                    terminalpp::detail::ascii::ZERO, 0 };

static constexpr byte HILITE_MOUSE_TRACKING[] =
                                  { terminalpp::detail::ascii::ONE,
                                    terminalpp::detail::ascii::ZERO,
                                    terminalpp::detail::ascii::ZERO,
                                    terminalpp::detail::ascii::ONE, 0 };

static constexpr byte CELL_MOTION_MOUSE_TRACKING[] =
                                  { terminalpp::detail::ascii::ONE,
                                    terminalpp::detail::ascii::ZERO,
                                    terminalpp::detail::ascii::ZERO,
                                    terminalpp::detail::ascii::TWO, 0 };

static constexpr byte ALL_MOTION_MOUSE_TRACKING[] =
                                  { terminalpp::detail::ascii::ONE,
                                    terminalpp::detail::ascii::ZERO,
                                    terminalpp::detail::ascii::ZERO,
                                    terminalpp::detail::ascii::THREE, 0 };

static constexpr byte USE_ALTERNATE_SCREEN_BUFFER[] =
                                  { terminalpp::detail::ascii::FOUR,
                                    terminalpp::detail::ascii::SEVEN, 0 };

}}}
