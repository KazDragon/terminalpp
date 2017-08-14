#pragma once
#include "terminalpp/ansi/protocol.hpp"
#include <iosfwd>

namespace terminalpp {

//* =========================================================================
// \brief A structure that represents a character set.
//* =========================================================================
struct character_set
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
/// \brief Inequality operator for character sets
//* =========================================================================
constexpr bool operator!=(character_set const &lhs, character_set const &rhs)
{
    return !(lhs == rhs);
}

//* =========================================================================
/// \brief Streaming output operator for character sets.  Outputs the name
/// of the character set.
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, character_set const &set);

}
