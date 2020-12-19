#pragma once

#include "terminalpp/colour.hpp"
#include "terminalpp/effect.hpp"
#include <boost/container_hash/hash.hpp>
#include <boost/operators.hpp>
#include <iosfwd>

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
        intensity intensity_effect = ansi::graphics::intensity::normal,
        underlining underlining_effect = ansi::graphics::underlining::not_underlined,
        polarity polarity_effect = ansi::graphics::polarity::positive,
        blinking blink_effect = ansi::graphics::blinking::steady)
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
    if (lhs.foreground_colour_ < rhs.foreground_colour_)
    {
        return true;
    }
    else if (lhs.foreground_colour_ == rhs.foreground_colour_)
    {
        if (lhs.background_colour_ < rhs.background_colour_)
        {
            return true;
        }
        else if (lhs.background_colour_ == rhs.background_colour_)
        {
            if (lhs.intensity_ < rhs.intensity_)
            {
                return true;
            }
            else if (lhs.intensity_ == rhs.intensity_)
            {
                if (lhs.underlining_ < rhs.underlining_)
                {
                    return true;
                }
                else if (lhs.underlining_ == rhs.underlining_)
                {
                    if (lhs.polarity_ < rhs.polarity_)
                    {
                        return true;
                    }
                    else if (lhs.polarity_ == rhs.polarity_)
                    {
                        if (lhs.blinking_ < rhs.blinking_)
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    
    return false;
}

//* =========================================================================
/// \brief Equality operator for attributes.
//* =========================================================================
constexpr bool operator==(attribute const &lhs, attribute const &rhs)
{
    return lhs.foreground_colour_ == rhs.foreground_colour_
        && lhs.background_colour_ == rhs.background_colour_
        && lhs.intensity_         == rhs.intensity_
        && lhs.underlining_       == rhs.underlining_
        && lhs.polarity_          == rhs.polarity_
        && lhs.blinking_          == rhs.blinking_;
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

