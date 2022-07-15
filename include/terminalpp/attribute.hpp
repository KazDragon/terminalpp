#pragma once

#include "terminalpp/colour.hpp"
#include "terminalpp/effect.hpp"
#include <boost/container_hash/hash.hpp>
#include <boost/operators.hpp>
#include <iosfwd>
#include <tuple>

namespace terminalpp {

//* =========================================================================
/// \brief A structure that carries around the presentation attributes of
/// an ANSI element.
//* =========================================================================
struct TERMINALPP_EXPORT attribute
  : private boost::less_than_comparable<attribute,
            boost::equality_comparable<attribute>>
{
    //* =====================================================================
    /// \brief Initialises the attribute with the colours and effects
    /// specified
    //* =====================================================================
    constexpr attribute(
        colour foreground_colour = colour(),
        colour background_colour = colour(),
        intensity intensity_effect = graphics::intensity::normal,
        underlining underlining_effect = graphics::underlining::not_underlined,
        polarity polarity_effect = graphics::polarity::positive,
        blinking blink_effect = graphics::blinking::steady)
      : foreground_colour_(foreground_colour),
        background_colour_(background_colour),
        intensity_(intensity_effect),
        underlining_(underlining_effect),
        polarity_(polarity_effect),
        blinking_(blink_effect)
    {
    }

    //* =====================================================================
    /// \brief Hash function
    //* =====================================================================
    friend std::size_t hash_value(attribute const &attr) noexcept
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, attr.foreground_colour_);
        boost::hash_combine(seed, attr.background_colour_);
        boost::hash_combine(seed, attr.intensity_);
        boost::hash_combine(seed, attr.underlining_);
        boost::hash_combine(seed, attr.polarity_);
        boost::hash_combine(seed, attr.blinking_);

        return seed;
    }

    // Graphics Attributes
    colour      foreground_colour_;
    colour      background_colour_;
    intensity   intensity_;
    underlining underlining_;
    polarity    polarity_;
    blinking    blinking_;
};

//* =========================================================================
/// \brief Less-than operator for attributes.
//* =========================================================================
constexpr bool operator<(attribute const &lhs, attribute const &rhs)
{
    return 
        std::tie(
            lhs.foreground_colour_, 
            lhs.background_colour_, 
            lhs.intensity_, 
            lhs.underlining_, 
            lhs.polarity_, 
            lhs.blinking_)
      < std::tie(
            rhs.foreground_colour_, 
            rhs.background_colour_, 
            rhs.intensity_, 
            rhs.underlining_, 
            rhs.polarity_, 
            rhs.blinking_);
}

//* =========================================================================
/// \brief Equality operator for attributes.
//* =========================================================================
constexpr bool operator==(attribute const &lhs, attribute const &rhs)
{
    return 
        std::tie(
            lhs.foreground_colour_, 
            lhs.background_colour_, 
            lhs.intensity_, 
            lhs.underlining_, 
            lhs.polarity_, 
            lhs.blinking_)
     == std::tie(
            rhs.foreground_colour_, 
            rhs.background_colour_, 
            rhs.intensity_, 
            rhs.underlining_, 
            rhs.polarity_, 
            rhs.blinking_);
}

//* =========================================================================
/// \brief Streaming output operator for attribute.  Prints the text
/// equivalent of the attribute (e.g. "foreground_colour[red],bold")
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, attribute const &attr);

}

namespace std {

template <>
struct hash<terminalpp::attribute>
{
    using argument_type = terminalpp::attribute;
    using result_type = std::size_t;

    result_type operator()(argument_type const &attr) const noexcept
    {
        return hash_value(attr);
    }
};

}

