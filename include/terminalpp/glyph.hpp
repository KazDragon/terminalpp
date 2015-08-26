#ifndef TERMINALPP_ANSI_GLYPH_HPP_
#define TERMINALPP_ANSI_GLYPH_HPP_

#include <iosfwd>
#include "terminalpp/ansi/protocol.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief A structure that carries around the character attributes of an
/// ANSI element.
//* =========================================================================
struct glyph
{
    //* =====================================================================
    /// \brief Default Constructor
    /// \par
    /// Note: the default glyph is chosen as a space character US ASCII
    /// locale.  That is, it is blank.
    //* =====================================================================
    constexpr glyph(
        char character = ' ',
        char locale    = terminalpp::ansi::character_set::LOCALE_US_ASCII)
      : character_(character),
        locale_(locale)
    {
    }

    // Character
    char character_;
    char locale_;
};

// ==========================================================================
// OPERATOR==
// ==========================================================================
constexpr bool operator==(glyph const &lhs, glyph const &rhs)
{
    return lhs.character_     == rhs.character_
        && lhs.locale_        == rhs.locale_;
}

// ==========================================================================
// OPERATOR!=
// ==========================================================================
constexpr bool operator!=(glyph const &lhs, glyph const &rhs)
{
    return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &out, glyph const &attr);

//* =========================================================================
/// \brief Returns whether a particular glyph is printable.
//* =========================================================================
bool is_printable(glyph const &gly);

}

#endif
