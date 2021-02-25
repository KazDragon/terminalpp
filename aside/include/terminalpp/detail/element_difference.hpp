#pragma once

#include "terminalpp/terminal.hpp"
#include <string>

namespace terminalpp {

struct behaviour;
struct element;

namespace detail {

//* =========================================================================
/// \brief Returns a string of ANSI codes that sets the attributes to the
/// default.
//* =========================================================================
byte_storage default_attribute();

//* =========================================================================
/// \brief Returns a string of ANSI codes that describes the difference
/// between two elements.
/// \par
/// Note: All members of the attribute and glyph structures are counted in
/// this, except for the character field, since that would need to be output
/// on each element, whereas other parts of the element that are the same
/// need not be output.
//* =========================================================================
byte_storage element_difference(
    element const &lhs,
    element const &rhs,
    behaviour const &terminal_behaviour);

}}
