#pragma once

#include "terminalpp/ansi/protocol.hpp"
#include "terminalpp/core.hpp"

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
    /// character set.  That is, it is blank.
    //* =====================================================================
    constexpr glyph(
        char character = ' ',
        terminalpp::ansi::charset charset =
            terminalpp::ansi::charset::us_ascii)
      : character_(character),
        charset_(charset)
    {
    }

    //* =====================================================================
    /// \brief Constructs a UTF-8 glyph from a char sequence
    //* =====================================================================
    explicit constexpr glyph(char const (&text)[2])
      : ucharacter_{text[0]},
        charset_(terminalpp::ansi::charset::utf8)
    {
    }

    //* =====================================================================
    /// \brief Constructs a UTF-8 glyph from a char sequence
    //* =====================================================================
    explicit constexpr glyph(char const (&text)[3])
      : ucharacter_{text[0], text[1]},
        charset_(terminalpp::ansi::charset::utf8)
    {
    }

    //* =====================================================================
    /// \brief Constructs a UTF-8 glyph from a char sequence
    //* =====================================================================
    explicit constexpr glyph(char const (&text)[4])
      : ucharacter_{text[0], text[1], text[2]},
        charset_(terminalpp::ansi::charset::utf8)
    {
    }

    //* =====================================================================
    /// \brief Constructs a UTF-8 glyph from a char sequence.
    //* =====================================================================
    template <class T = void> // This makes matching these parameters "worse"
                              // than any of the array matches above, and so
                              // avoids ambiguity.
    explicit glyph(char const *ustr)
      : ucharacter_{0},
        charset_(terminalpp::ansi::charset::utf8)
    {
        for (size_t index = 0; index < sizeof(ucharacter_); ++index)
        {
            ucharacter_[index] = ustr[index];

            if (!(ucharacter_[index] & 0x80))
            {
                break;
            }
        }
    }

    union {
        char character_;
        char ucharacter_[3];
    };

    terminalpp::ansi::charset charset_;
};

// ==========================================================================
// OPERATOR==
// ==========================================================================
constexpr bool operator==(glyph const &lhs, glyph const &rhs)
{
    return lhs.character_ == rhs.character_
        && lhs.charset_   == rhs.charset_;
}

// ==========================================================================
// OPERATOR!=
// ==========================================================================
constexpr bool operator!=(glyph const &lhs, glyph const &rhs)
{
    return !(lhs == rhs);
}

//* =========================================================================
/// \brief Returns whether a particular glyph is printable.
//* =========================================================================
TERMINALPP_EXPORT
bool is_printable(glyph const &gly);

}
