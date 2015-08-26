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
    /// Note: the default glyph is chosen as a space character in the G0
    /// character set in the US ASCII locale.  That is, it is blank.
    //* =====================================================================
    constexpr glyph(
        char character     = ' ',
        char character_set = terminalpp::ansi::character_set::CHARACTER_SET_G0,
        char locale        = terminalpp::ansi::character_set::LOCALE_US_ASCII)
      : character_(character),
        character_set_(character_set),
        locale_(locale)
    {
    }

    // Character
    char character_;

    // Character Set Attributes
    char character_set_;
    char locale_;
};

// ==========================================================================
// OPERATOR==
// ==========================================================================
constexpr bool operator==(glyph const &lhs, glyph const &rhs)
{
    return lhs.character_     == rhs.character_
        && lhs.character_set_ == rhs.character_set_
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
