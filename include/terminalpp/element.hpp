#pragma once

#include "terminalpp/attribute.hpp"
#include "terminalpp/glyph.hpp"
#include <boost/operators.hpp>
#include <iosfwd>
#include <utility>

namespace terminalpp {

//* =========================================================================
/// \brief A structure that represents the fundamental printable element of
/// a terminal screen, which comprises a glyph modified by a set of
/// attribute (such as colour, intensity, etc.)
//* =========================================================================
struct element
  : private boost::less_than_comparable<element,
            boost::equality_comparable<element>>
{
    //* =====================================================================
    /// \brief Value Constructor
    //* =====================================================================
    constexpr element(
        terminalpp::glyph gly = {},
        terminalpp::attribute attr = {})
      : glyph_(std::move(gly)),
        attribute_(std::move(attr))
    {
    }

    //* =====================================================================
    /// \brief Char Constructor
    //* =====================================================================
    constexpr element(
        char ch,
        terminalpp::attribute attr = {})
      : element(terminalpp::glyph(ch), attr)
    {
    }

    terminalpp::glyph     glyph_;
    terminalpp::attribute attribute_;
};

//* =========================================================================
/// \brief Less-than Operator
//* =========================================================================
constexpr bool operator<(element const &lhs, element const &rhs)
{
    return lhs.glyph_ < rhs.glyph_
        || (lhs.glyph_ == rhs.glyph_ && lhs.attribute_ < rhs.attribute_);
}

//* =========================================================================
/// \brief Equality Operator
//* =========================================================================
constexpr bool operator==(element const &lhs, element const &rhs)
{
    return lhs.glyph_     == rhs.glyph_
        && lhs.attribute_ == rhs.attribute_;
}

//* =========================================================================
/// \brief Streaming output operator for element.  Prints the text
/// equivalent of the element (e.g. "glyph[c],attribute[red]").
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, element const &elem);

}
