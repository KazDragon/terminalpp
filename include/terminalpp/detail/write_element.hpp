#ifndef TERMINALPP_DETAIL_WRITE_ELEMENT_HPP_
#define TERMINALPP_DETAIL_WRITE_ELEMENT_HPP_

namespace terminalpp { 

class element;

namespace detail {

//* =========================================================================
/// \brief Returns a string of ANSI codes that represents the character
/// being written.
//* =========================================================================
std::string write_element(element const &elem);

}}

#endif
