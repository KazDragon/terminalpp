#pragma once
#include "terminalpp/ansi/protocol.hpp"
#include <boost/container_hash/hash.hpp>
#include <boost/operators.hpp>
#include <iosfwd>

namespace terminalpp {

//* =========================================================================
// \brief A structure that represents a character set.
//* =========================================================================
struct TERMINALPP_EXPORT character_set
  : private boost::less_than_comparable<character_set,
            boost::equality_comparable<character_set>>
{
    //* =====================================================================
    /// \brief Initialises the character set to its default value.
    //* =====================================================================
    constexpr character_set()
      : character_set(ansi::charset::us_ascii)
    {
    }

    //* =====================================================================
    /// \brief Initialises the character set the given value.
    //* =====================================================================
    constexpr character_set(ansi::charset const &set)
      : value_(set)
    {
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

    terminalpp::ansi::charset value_;
};

//* =========================================================================
/// \brief Equality operator for character sets
//* =========================================================================
constexpr bool operator==(character_set const &lhs, character_set const &rhs)
{
    return lhs.value_ == rhs.value_;
}

//* =========================================================================
/// \brief Less-than operator for character sets
//* =========================================================================
constexpr bool operator<(character_set const &lhs, character_set const &rhs)
{
    return lhs.value_ < rhs.value_;
}

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
