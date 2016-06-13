#pragma once

#include "terminalpp/ansi/charset.hpp"
#include <string>

namespace terminalpp { namespace detail {

// Character Sets
std::string select_default_charset();
std::string select_utf8_charset();
std::string designate_g0_charset(terminalpp::ansi::charset const &cs);
std::string designate_g1_charset(terminalpp::ansi::charset const &cs);
std::string designate_g2_charset(terminalpp::ansi::charset const &cs);
std::string designate_g3_charset(terminalpp::ansi::charset const &cs);

}}
