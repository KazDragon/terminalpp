#pragma once

#include "terminalpp/detail/ascii.hpp"

namespace terminalpp { namespace ansi {

// Sequence for introducing DEC Private Mode
static constexpr char const DEC_PRIVATE_MODE[] = { terminalpp::detail::ascii::QUESTION_MARK, 0 };

//* =========================================================================
/// \namespace terminalpp::ansi::dec_pm
/// \brief Contains all of the constants for the commands that begin with the
/// DEC Private Mode sequence.
//* =========================================================================
namespace dec_pm {

static constexpr char const SET[]    = { terminalpp::detail::ascii::LOWERCASE_H, 0 };
static constexpr char const RESET[]  = { terminalpp::detail::ascii::LOWERCASE_L, 0 };

// Set = cursor visible; Reset = cursor hidden
static constexpr char const CURSOR[] = { terminalpp::detail::ascii::TWO,
                                         terminalpp::detail::ascii::FIVE, 0 };

// Set = use basic mouse tracking.  Reset =  stop using basic mouse tracking.
static constexpr char const BASIC_MOUSE_TRACKING[] =
                                        { terminalpp::detail::ascii::ONE,
                                          terminalpp::detail::ascii::ZERO,
                                          terminalpp::detail::ascii::ZERO,
                                          terminalpp::detail::ascii::ZERO, 0 };

static constexpr char const HILITE_MOUSE_TRACKING[] =
                                        { terminalpp::detail::ascii::ONE,
                                          terminalpp::detail::ascii::ZERO,
                                          terminalpp::detail::ascii::ZERO,
                                          terminalpp::detail::ascii::ONE, 0 };

static constexpr char const CELL_MOTION_MOUSE_TRACKING[] =
                                        { terminalpp::detail::ascii::ONE,
                                          terminalpp::detail::ascii::ZERO,
                                          terminalpp::detail::ascii::ZERO,
                                          terminalpp::detail::ascii::TWO, 0 };

static constexpr char const ALL_MOTION_MOUSE_TRACKING[] =
                                        { terminalpp::detail::ascii::ONE,
                                          terminalpp::detail::ascii::ZERO,
                                          terminalpp::detail::ascii::ZERO,
                                          terminalpp::detail::ascii::THREE, 0 };

}}}
