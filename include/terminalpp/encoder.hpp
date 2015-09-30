#ifndef TERMINALPP_DETAIL_ENCODER_HPP_
#define TERMINALPP_DETAIL_ENCODER_HPP_

#include "terminalpp/string.hpp"
#include <string>

namespace terminalpp
{

//* =========================================================================
/// \brief A function that converts a std::string into a terminalpp::string,
/// parsing its contents according to the String To Elements protocol.
//* =========================================================================
terminalpp::string encode(std::string const &text);

//* =========================================================================
/// \brief A function that converts a char* into a terminalpp::string,
/// parsing its contents according to the String To Elements protocol.
//* =========================================================================
terminalpp::string encode(char const *text);

//* =========================================================================
/// \brief A function that converts a char* of a given length into a 
/// terminalpp::string, parsing its contents according to the String To
/// Elements protocol.
//* =========================================================================
terminalpp::string encode(char const *text, size_t length);

}

#endif
