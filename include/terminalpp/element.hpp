#pragma once

#include "terminalpp/attribute.hpp"
#include "terminalpp/glyph.hpp"
#include <utility>

namespace terminalpp {

//* =========================================================================
/// \brief A structure that represents the fundamental printable element of
/// a terminal screen, which comprises a glyph modified by a set of
/// attribute (such as colour, intensity, etc.)
//* =========================================================================
struct element
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
/// \brief Equality Operator
//* =========================================================================
constexpr bool operator==(element const &lhs, element const &rhs)
{
    return lhs.glyph_     == rhs.glyph_
        && lhs.attribute_ == rhs.attribute_;
}

//* =========================================================================
/// \brief Inequality Operator
//* =========================================================================
constexpr bool operator!=(element const &lhs, element const &rhs)
{
    return !(lhs == rhs);
}

}
