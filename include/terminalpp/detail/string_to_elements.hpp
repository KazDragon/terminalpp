#ifndef TERMINALPP_DETAIL_STRING_TO_ELEMENTS_HPP_
#define TERMINALPP_DETAIL_STRING_TO_ELEMENTS_HPP_

#include "terminalpp/element.hpp"
#include <string>
#include <vector>

namespace terminalpp {

namespace detail {

//* =========================================================================
/// \brief A function that applies the string_to_elements parser to a string.
//* =========================================================================
std::vector<::terminalpp::element> string_to_elements(std::string const &text);

//* =========================================================================
/// \brief A function that applies the string_to_elements parser to a string.
//* =========================================================================
std::vector<::terminalpp::element> string_to_elements(char const *text);

//* =========================================================================
/// \brief A function that applies the string_to_elements parser to a string.
//* =========================================================================
std::vector<::terminalpp::element> string_to_elements(char const *text, size_t len);

}}

#endif
