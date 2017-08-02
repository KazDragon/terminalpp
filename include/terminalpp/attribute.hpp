#pragma once

#include "terminalpp/ansi/protocol.hpp"
#include <iosfwd>

namespace terminalpp {

//* =========================================================================
/// \brief Structure representing a normal ANSI 16-colour value
//* =========================================================================
struct low_colour
{
    //* =====================================================================
    /// \brief Constructs a low_colour with the "default" colour value.
    //* =====================================================================
    constexpr low_colour()
        : low_colour(terminalpp::ansi::graphics::colour::default_)
    {
    }

    //* =====================================================================
    /// \brief Constructs a low_colour from the passed-in ANSI colour.
    //* =====================================================================
    constexpr low_colour(terminalpp::ansi::graphics::colour colour)
        : value_(colour)
    {
    };

    terminalpp::ansi::graphics::colour value_;
};

//* =========================================================================
/// \brief Equality operator for low_colours.
//* =========================================================================
constexpr bool operator==(low_colour const &lhs, low_colour const &rhs)
{
    return lhs.value_ == rhs.value_;
}

//* =========================================================================
/// \brief Inequality operator for low_colours.
//* =========================================================================
constexpr bool operator!=(low_colour const &lhs, low_colour const &rhs)
{
    return !(lhs == rhs);
}

//* =========================================================================
/// \brief Streaming output operator for low_colours.  Prints the text
/// equivalent of the colour (e.g. red, blue, black)
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, low_colour const &col);

//* =========================================================================
/// \brief Structure representing the central 216 colours of a 256-colour
/// palette, where each colour channel is represented by a number in the
/// range 0..5.
//* =========================================================================
struct high_colour
{
    //* =====================================================================
    /// \brief Default constructs a high-colour with the value of pure black.
    //* =====================================================================
    constexpr high_colour()
      : high_colour(0, 0, 0)
    {
    }

    //* =====================================================================
    /// \brief Constructs a high_colour from the passed-in RGB values, each
    /// of which should be in the range 0-5.
    //* =====================================================================
    constexpr high_colour(
        byte red,
        byte green,
        byte blue)
      : value_(red * 36 + green * 6 + blue + 16)
    {
    }

    byte value_;
};

//* =========================================================================
/// \brief Equality operator for high_colours.
//* =========================================================================
constexpr bool operator==(high_colour const &lhs, high_colour const &rhs)
{
    return lhs.value_ == rhs.value_;
}

//* =========================================================================
/// \brief Inequality operator for high_colours.
//* =========================================================================
constexpr bool operator!=(high_colour const &lhs, high_colour const &rhs)
{
    return !(lhs == rhs);
}

//* =========================================================================
/// \brief Streaming output operator for high_colours.  Prints the text
/// equivalent of the colour (e.g. #234, #512, etc.)
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, high_colour const &col);

//* =========================================================================
/// \brief Structure representing the 24 greyscale tones of a 256-colour
/// palette
//* =========================================================================
struct greyscale_colour
{
    //* =====================================================================
    /// \brief Default constructs a greyscale value with the darkest
    /// available grey.
    //* =====================================================================
    constexpr greyscale_colour()
      : shade_(0)
    {
    }

    //* =====================================================================
    /// \brief Constructs a greyscale value from the given shade, which
    /// should be in the range 0-23.
    //* =====================================================================
    constexpr explicit greyscale_colour(byte shade)
      : shade_(shade + 232)
    {
    }

    byte shade_;
};

//* =========================================================================
/// \brief Equality operator for greyscale_colours.
//* =========================================================================
constexpr bool operator==(
    greyscale_colour const &lhs, greyscale_colour const &rhs)
{
    return lhs.shade_ == rhs.shade_;
}

//* =========================================================================
/// \brief Inequality operator for greyscale_colours.
//* =========================================================================
constexpr bool operator!=(
    greyscale_colour const &lhs, greyscale_colour const &rhs)
{
    return !(lhs == rhs);
}

//* =========================================================================
/// \brief Streaming output operator for greyscale_colours.  Prints the text
/// equivalent of the colour (e.g. #22, #00, etc.)
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, greyscale_colour const &col);

//* =========================================================================
/// \brief Structure representing a sum type of the available colour styles.
//* =========================================================================
struct colour
{
    //* =====================================================================
    /// \brief An enumeration of the possible colour types.
    //* =====================================================================
    enum class type : byte
    {
        low, high, greyscale
    };

    //* =====================================================================
    /// \brief Default constructs the colour with the "default" ANSI colour.
    //* =====================================================================
    constexpr colour()
      : colour(terminalpp::low_colour())
    {
    }

    //* =====================================================================
    /// \brief Constructs a colour with the passed low_colour value.
    //* =====================================================================
    constexpr colour(terminalpp::low_colour col)
      : low_colour_(std::move(col)),
        type_(type::low)
    {
    }

    //* =====================================================================
    /// \brief Constructs a colour with the passed high_colour value.
    //* =====================================================================
    constexpr colour(terminalpp::high_colour col)
      : high_colour_(std::move(col)),
        type_(type::high)
    {
    }

    //* =====================================================================
    /// \brief Constructs a colour with the passed greyscale_colour value.
    //* =====================================================================
    constexpr colour(terminalpp::greyscale_colour col)
      : greyscale_colour_(std::move(col)),
        type_(type::greyscale)
    {
    }

    //* =====================================================================
    /// \brief Copy constructor
    //* =====================================================================
    constexpr colour(terminalpp::ansi::graphics::colour col)
      : colour(terminalpp::low_colour(col))
    {
    }

    union
    {
        terminalpp::low_colour low_colour_;
        terminalpp::high_colour high_colour_;
        terminalpp::greyscale_colour greyscale_colour_;
    };

    type type_;
};

//* =========================================================================
/// \brief Equality operator for colours.
//* =========================================================================
constexpr bool operator==(colour const &lhs, colour const &rhs)
{
    return lhs.type_             == rhs.type_
        && lhs.type_             == colour::type::low
         ? lhs.low_colour_       == rhs.low_colour_
         : lhs.type_             == colour::type::high
         ? lhs.high_colour_      == rhs.high_colour_
         : lhs.type_             == colour::type::greyscale
         ? lhs.greyscale_colour_ == rhs.greyscale_colour_
         : false;
}

//* =========================================================================
/// \brief Inequality operator for colours.
//* =========================================================================
constexpr bool operator!=(colour const &lhs, colour const &rhs)
{
    return !(lhs == rhs);
}

//* =========================================================================
/// \brief Streaming output operator for colours.  Prints the text equivalent
/// of the colour (e.g. "red", "#234", "#07", etc.)
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, colour const &col);

//* =========================================================================
/// \brief A traits class for which attribute is the "default" one.
///
//* =========================================================================
template <class Type>
struct graphics_attribute_default_setting;

//* =========================================================================
/// \brief A structure representing an ANSI graphics attribute (e.g.
/// intensity, underlining)
//* =========================================================================
template <class Type>
struct graphics_attribute
{
    //* =====================================================================
    /// \brief Initialises the intensity to the default (normal) value
    //* =====================================================================
    constexpr graphics_attribute()
      : graphics_attribute(
            graphics_attribute_default_setting<Type>::value)
    {
    }

    //* =====================================================================
    /// \brief Initialises the intensity to the given value
    //* =====================================================================
    constexpr graphics_attribute(Type value)
      : value_(value)
    {
    }

    Type value_;
};

//* =========================================================================
/// \brief Equality for graphics attributes.
//* =========================================================================
template <class Type>
constexpr bool operator==(
    graphics_attribute<Type> const &lhs,
    graphics_attribute<Type> const &rhs)
{
    return lhs.value_ == rhs.value_;
}

//* =========================================================================
/// \brief Inequality for graphics attributes.
//* =========================================================================
template <class Type>
constexpr bool operator!=(
    graphics_attribute<Type> const &lhs,
    graphics_attribute<Type> const &rhs)
{
    return !(lhs == rhs);
}

//* =========================================================================
/// \brief Specialization for intensity default case (normal intensity)
//* =========================================================================
template <>
struct graphics_attribute_default_setting<terminalpp::ansi::graphics::intensity>
  : std::integral_constant<
        terminalpp::ansi::graphics::intensity,
        terminalpp::ansi::graphics::intensity::normal
    >
{
};

//* =========================================================================
/// \brief Specialization for underlining default case (not underlined)
//* =========================================================================
template <>
struct graphics_attribute_default_setting<terminalpp::ansi::graphics::underlining>
  : std::integral_constant<
        terminalpp::ansi::graphics::underlining,
        terminalpp::ansi::graphics::underlining::not_underlined
    >
{
};

//* =========================================================================
/// \brief Specialization for polarity default case (positive)
//* =========================================================================
template <>
struct graphics_attribute_default_setting<terminalpp::ansi::graphics::polarity>
  : std::integral_constant<
        terminalpp::ansi::graphics::polarity,
        terminalpp::ansi::graphics::polarity::positive
    >
{
};

//* =========================================================================
/// \brief Specialization for blinking default case (steady)
//* =========================================================================
template <>
struct graphics_attribute_default_setting<terminalpp::ansi::graphics::blinking>
  : std::integral_constant<
        terminalpp::ansi::graphics::blinking,
        terminalpp::ansi::graphics::blinking::steady
    >
{
};

using intensity   = graphics_attribute<terminalpp::ansi::graphics::intensity>;
using underlining = graphics_attribute<terminalpp::ansi::graphics::underlining>;
using polarity    = graphics_attribute<terminalpp::ansi::graphics::polarity>;
using blinking    = graphics_attribute<terminalpp::ansi::graphics::blinking>;

//* =========================================================================
/// \brief Streaming output operator for intensities.  Prints the text
/// equivalent of the intensity (e.g. "normal", "bold", "faint").
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, intensity const &effect);

//* =========================================================================
/// \brief Streaming output operator for underlining.  Prints the text
/// equivalent of the underlining (e.g. "underlined", "not underlined").
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, underlining const &effect);

//* =========================================================================
/// \brief Streaming output operator for polarities.  Prints the text
/// equivalent of the polarity (e.g. "positive", "negative").
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, polarity const &effect);

//* =========================================================================
/// \brief Streaming output operator for blinking.  Prints the text
/// equivalent of the blink effect (e.g. "blinking", "steady").
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, blinking const &effect);

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
/// equivalent of the attribute (e.g. "foreground_colour[red]")
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, attribute const &attr);

}
