#pragma once

#include "terminalpp/colour.hpp"
#include "terminalpp/effect.hpp"
#include <iosfwd>

namespace terminalpp {

//* =========================================================================
/// \brief A structure that carries around the presentation attributes of
/// an ANSI element.
//* =========================================================================
struct attribute
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

    // Graphics Attributes
    colour      foreground_colour_;
    colour      background_colour_;
    intensity   intensity_;
    underlining underlining_;
    polarity    polarity_;
    blinking    blinking_;
};

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
/// \brief Inequality operator for attributes.
//* =========================================================================
constexpr bool operator!=(attribute const &lhs, attribute const &rhs)
{
    return !(lhs == rhs);
}

//* =========================================================================
/// \brief Streaming output operator for attribute.  Prints the text
/// equivalent of the attribute (e.g. "foreground_colour[red],bold")
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, attribute const &attr);

}
