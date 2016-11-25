#pragma once

#include "terminalpp/ansi/protocol.hpp"
#include "terminalpp/core.hpp"

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
        terminalpp::u8 red,
        terminalpp::u8 green,
        terminalpp::u8 blue)
      : value_(red * 36 + green * 6 + blue + 16)
    {
    }

    terminalpp::u8 value_;
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
    constexpr explicit greyscale_colour(terminalpp::u8 shade)
      : shade_(shade + 232)
    {
    }

    terminalpp::u8 shade_;
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
/// \brief Structure representing a sum type of the available colour styles.
//* =========================================================================
struct colour
{
    //* =====================================================================
    /// \brief An enumeration of the possible colour types.
    //* =====================================================================
    enum class type : terminalpp::u8
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
/// \brief A structure that carries around the presentation attributes of
/// an ANSI element.
//* =========================================================================
struct attribute
{
    //* =====================================================================
    /// \brief Initialises the attribute to having the default colour,
    /// no intensity, no underlining, and normal polarity.
    //* =====================================================================
    constexpr attribute()
      : intensity_(terminalpp::ansi::graphics::intensity::normal),
        underlining_(terminalpp::ansi::graphics::underlining::not_underlined),
        polarity_(terminalpp::ansi::graphics::polarity::positive),
        blinking_(terminalpp::ansi::graphics::blinking::steady)
    {
    }

    // Graphics Attributes
    colour                                  foreground_colour_;
    colour                                  background_colour_;
    terminalpp::ansi::graphics::intensity   intensity_;
    terminalpp::ansi::graphics::underlining underlining_;
    terminalpp::ansi::graphics::polarity    polarity_;
    terminalpp::ansi::graphics::blinking    blinking_;
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

}
