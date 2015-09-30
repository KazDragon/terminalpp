#ifndef TERMINAL_ANSI_DEC_PRIVATE_MODE
#define TERMINAL_ANSI_DEC_PRIVATE_MODE

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

}}}

#endif
