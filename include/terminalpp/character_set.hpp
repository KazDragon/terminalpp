#pragma once
#include "terminalpp/core.hpp"
#include <boost/container_hash/hash.hpp>
#include <boost/operators.hpp>
#include <boost/optional.hpp>
#include <iosfwd>

namespace terminalpp {

//* =========================================================================
/// \brief An enumeration for all supported character sets.
//* =========================================================================
enum class charset : char {
    dec,
    dec_supplementary,
    dec_supplementary_graphics,
    dec_technical,
    uk,
    us_ascii,
    dutch,
    finnish,
    french,
    french_canadian,
    german,
    italian,
    danish,
    portuguese,
    spanish,
    swedish,
    swiss,
    sco,
    utf8,
};

//* =========================================================================
/// \brief A structure that represents a character set.
//* =========================================================================
struct TERMINALPP_EXPORT character_set
  : private boost::less_than_comparable<character_set,
            boost::equality_comparable<character_set>>
{
    //* =====================================================================
    /// \brief Initialises the character set to its default value.
    //* =====================================================================
    constexpr character_set()
      : character_set(charset::us_ascii)
    {
    }

    //* =====================================================================
    /// \brief Initialises the character set the given value.
    //* =====================================================================
    constexpr character_set(charset const &set)
      : value_(set)
    {
    }

    //* =====================================================================
    /// \brief Equality operator for character sets
    //* =====================================================================
    constexpr friend bool operator==(
        character_set const &lhs, 
        character_set const &rhs)
    {
        return lhs.value_ == rhs.value_;
    }

    //* =====================================================================
    /// \brief Less-than operator for character sets
    //* =====================================================================
    constexpr friend bool operator<(
        character_set const &lhs, 
        character_set const &rhs)
    {
        return lhs.value_ < rhs.value_;
    }

    //* =====================================================================
    /// \brief Hash function
    //* =====================================================================
    friend std::size_t hash_value(character_set const &cs) noexcept
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, cs.value_);

        return seed;
    }

    terminalpp::charset value_;
};

//* =========================================================================
/// \brief Looks up a character set from a set of ANSI bytes.
//* =========================================================================
TERMINALPP_EXPORT
boost::optional<character_set> lookup_character_set(bytes code);

//* =========================================================================
/// \brief Encodes a character set into a set of ANSI bytes.
//* =========================================================================
TERMINALPP_EXPORT
byte_storage encode_character_set(character_set const &set);

//* =========================================================================
/// \brief Streaming output operator for character sets.  Outputs the name
/// of the character set.
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, character_set const &set);

}

namespace std {

template <>
struct hash<terminalpp::character_set>
{
    using argument_type = terminalpp::character_set;
    using result_type = std::size_t;

    result_type operator()(argument_type const &cs) const noexcept
    {
        return hash_value(cs);
    }
};

}
