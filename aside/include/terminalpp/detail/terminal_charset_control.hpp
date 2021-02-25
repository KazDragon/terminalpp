#pragma once

#include "terminalpp/ansi/charset.hpp"

namespace terminalpp { namespace detail {

// Character Sets
byte_storage select_default_charset();
byte_storage select_utf8_charset();
byte_storage designate_g0_charset(terminalpp::ansi::charset const &cs);
byte_storage designate_g1_charset(terminalpp::ansi::charset const &cs);
byte_storage designate_g2_charset(terminalpp::ansi::charset const &cs);
byte_storage designate_g3_charset(terminalpp::ansi::charset const &cs);

}}
