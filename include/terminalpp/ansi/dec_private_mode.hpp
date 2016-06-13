#pragma once

#include "terminalpp/detail/ascii.hpp"

namespace terminalpp { namespace ansi {

// Sequence for introducing DEC Private Mode
static constexpr char const DEC_PRIVATE_MODE[] = { terminalpp::ascii::QUESTION_MARK, 0 };

namespace dec_pm {

static constexpr char const SET[]    = { terminalpp::ascii::LOWERCASE_H, 0 };
static constexpr char const RESET[]  = { terminalpp::ascii::LOWERCASE_L, 0 };

// Set = cursor visible; Reset = cursor hidden
static constexpr char const CURSOR[] = { terminalpp::ascii::TWO,
                                         terminalpp::ascii::FIVE, 0 };

// Set = use basic mouse tracking.  Reset =  stop using basic mouse tracking.
static constexpr char const BASIC_MOUSE_TRACKING[] =
                                        { terminalpp::ascii::ONE,
                                          terminalpp::ascii::ZERO,
                                          terminalpp::ascii::ZERO,
                                          terminalpp::ascii::ZERO, 0 };

static constexpr char const HILITE_MOUSE_TRACKING[] =
                                        { terminalpp::ascii::ONE,
                                          terminalpp::ascii::ZERO,
                                          terminalpp::ascii::ZERO,
                                          terminalpp::ascii::ONE, 0 };

static constexpr char const CELL_MOTION_MOUSE_TRACKING[] =
                                        { terminalpp::ascii::ONE,
                                          terminalpp::ascii::ZERO,
                                          terminalpp::ascii::ZERO,
                                          terminalpp::ascii::TWO, 0 };

static constexpr char const ALL_MOTION_MOUSE_TRACKING[] =
                                        { terminalpp::ascii::ONE,
                                          terminalpp::ascii::ZERO,
                                          terminalpp::ascii::ZERO,
                                          terminalpp::ascii::THREE, 0 };

}}}
