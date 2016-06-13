#pragma once

#include "terminalpp/core.hpp"
#include "terminalpp/ansi/control_characters.hpp"
#include "terminalpp/ansi/charset.hpp"
#include "terminalpp/ansi/csi.hpp"
#include "terminalpp/ansi/dec_private_mode.hpp"
#include "terminalpp/ansi/graphics.hpp"
#include "terminalpp/ansi/mouse.hpp"
#include "terminalpp/ansi/ss3.hpp"
#include "terminalpp/detail/ascii.hpp"

namespace terminalpp { namespace ansi {

// Single Character Functions and other supporting characters
static char const PS = terminalpp::ascii::SEMI_COLON; // Parameter Separator

}}
