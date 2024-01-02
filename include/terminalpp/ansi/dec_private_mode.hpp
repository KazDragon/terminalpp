#pragma once

#include "terminalpp/detail/ascii.hpp"

namespace terminalpp::ansi {

// Sequence for introducing DEC Private Mode (extension to CSI, so the
// usual sequence comes first.)
static constexpr byte dec_private_mode[] = {
    terminalpp::detail::ascii::question_mark};

//* =========================================================================
/// \namespace terminalpp::ansi::dec_pm
/// \brief Contains all of the constants for the commands that begin with the
/// DEC Private Mode sequence.
//* =========================================================================
namespace dec_pm {

// clang-format off
static constexpr byte set[]    = { terminalpp::detail::ascii::lowercase_h };
static constexpr byte reset[]  = { terminalpp::detail::ascii::lowercase_l };

// Set = cursor visible; Reset = cursor hidden
static constexpr byte cursor[] = { terminalpp::detail::ascii::two,
                                   terminalpp::detail::ascii::five };

// Set = use basic mouse tracking.  Reset =  stop using basic mouse tracking.
static constexpr byte basic_mouse_tracking[] =
                                  { terminalpp::detail::ascii::one,
                                    terminalpp::detail::ascii::zero,
                                    terminalpp::detail::ascii::zero,
                                    terminalpp::detail::ascii::zero };

static constexpr byte hilite_mouse_tracking[] =
                                  { terminalpp::detail::ascii::one,
                                    terminalpp::detail::ascii::zero,
                                    terminalpp::detail::ascii::zero,
                                    terminalpp::detail::ascii::one };

static constexpr byte cell_motion_mouse_tracking[] =
                                  { terminalpp::detail::ascii::one,
                                    terminalpp::detail::ascii::zero,
                                    terminalpp::detail::ascii::zero,
                                    terminalpp::detail::ascii::two };

static constexpr byte all_motion_mouse_tracking[] =
                                  { terminalpp::detail::ascii::one,
                                    terminalpp::detail::ascii::zero,
                                    terminalpp::detail::ascii::zero,
                                    terminalpp::detail::ascii::three };

static constexpr byte use_alternate_screen_buffer[] =
                                  { terminalpp::detail::ascii::four,
                                    terminalpp::detail::ascii::seven };
// clang-format on

}  // namespace dec_pm
}  // namespace terminalpp::ansi
