#pragma once

#include "terminalpp/ansi/protocol.hpp"
#include "terminalpp/character_set.hpp"
#include <boost/container_hash/hash.hpp>
#include <boost/operators.hpp>
#include <iosfwd>

namespace terminalpp {

//* =========================================================================
/// \brief A structure that carries around the character attributes of an
/// ANSI element.
//* =========================================================================
struct glyph
  : private boost::less_than_comparable<glyph,
            boost::equality_comparable<glyph>>
{
    //* =====================================================================
    /// \brief Default Constructor
    /// \par
    /// Note: the default glyph is chosen as a space character US ASCII
    /// character set.  That is, it is blank.
    //* =====================================================================
    constexpr glyph(
        char character = ' ',
        character_set charset = character_set())
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
    explicit constexpr glyph(char const *ustr)
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

    //* =====================================================================
    /// \brief Hash function
    //* =====================================================================
    friend std::size_t hash_value(glyph const &gly) noexcept
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, gly.charset_);

        if (gly.charset_ == terminalpp::ansi::charset::utf8)
        {
            for (auto ch : gly.ucharacter_)
            {
                boost::hash_combine(seed, ch);
            }
        }
        else
        {
            boost::hash_combine(seed, gly.character_);
        }

        return seed;
    }

    union {
        char character_;
        char ucharacter_[3];
    };

    character_set charset_;
};

// ==========================================================================
// OPERATOR==
// ==========================================================================
constexpr bool operator==(glyph const &lhs, glyph const &rhs)
{
    if (lhs.charset_ == rhs.charset_)
    {
        if (lhs.charset_ == terminalpp::ansi::charset::utf8)
        {
            using std::begin;
            using std::end;

            // Re-implementing std::equal here for constexprness.
            for (auto lch = begin(lhs.ucharacter_), rch = begin(rhs.ucharacter_);
                 lch != end(lhs.ucharacter_);
                 ++lch, ++rch)
            {
                if (*lch != *rch)
                {
                    return false;
                }
            }

            return true;
        }
        else
        {
            return lhs.character_ == rhs.character_;
        }
    }

    return false;
}

// ==========================================================================
// OPERATOR<
// ==========================================================================
constexpr bool operator<(glyph const &lhs, glyph const &rhs)
{
    if (lhs.charset_ < rhs.charset_)
    {
        return true;
    }

    if (lhs.charset_ == rhs.charset_)
    {
        if (lhs.charset_ == terminalpp::ansi::charset::utf8)
        {
            using std::begin;
            using std::end;

            // Reimplementing lexicographical_compare here for constexprness.
            for (auto begin1 = begin(lhs.ucharacter_),
                      end1   = end(lhs.ucharacter_),
                      begin2 = begin(rhs.ucharacter_);
                 begin1 != end1;
                 ++begin1, ++begin2)
            {
                // We are expecting unicode characters to be ordered so that
                // outside of the ASCII range is greater, so therefore we must
                // remove the sign from these comparisons.
                if (byte(*begin1) < byte(*begin2)) return true;
                if (byte(*begin2) < byte(*begin1)) return false;
            }
            
            return false;
        }
        else
        {
            return lhs.character_ < rhs.character_;
        }
    }
    
    return false;
}

//* =========================================================================
/// \brief Returns whether a particular glyph is printable.
//* =========================================================================
TERMINALPP_EXPORT
bool is_printable(glyph const &gly);

//* =========================================================================
/// \brief Streaming output operator for glyph.  Prints the text
/// equivalent of the element (e.g. "c", "U+2048", "uk:£")
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, glyph const &gly);

}

namespace std {

template <>
struct hash<terminalpp::glyph>
{
    using argument_type = terminalpp::glyph;
    using result_type = std::size_t;

    result_type operator()(argument_type const &elem) const noexcept
    {
        return hash_value(elem);
    }
};

}
