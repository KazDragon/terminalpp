#ifndef TERMINALPP_ANSI_ATTRIBUTE_HPP_
#define TERMINALPP_ANSI_ATTRIBUTE_HPP_

#include "terminalpp/ansi/protocol.hpp"
#include "terminalpp/core.hpp"
#include <iosfwd>

namespace terminalpp {

//* =========================================================================
/// \brief Structure representing a normal ANSI 16-colour value
//* =========================================================================
struct low_colour
{
    constexpr low_colour()
        : low_colour(terminalpp::ansi::graphics::colour::default_)
    {
    }

    constexpr low_colour(char value)
        : low_colour(terminalpp::ansi::graphics::colour(value))
    {
    }

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
    constexpr high_colour()
      : high_colour(0, 0, 0)
    {
    }

    constexpr high_colour(
        terminalpp::u8 red,
        terminalpp::u8 green,
        terminalpp::u8 blue)
      : red_(red),
        green_(green),
        blue_(blue)
    {
    }

    terminalpp::u8 red_;
    terminalpp::u8 green_;
    terminalpp::u8 blue_;
};

//* =========================================================================
/// \brief Equality operator for high_colours.
//* =========================================================================
constexpr bool operator==(high_colour const &lhs, high_colour const &rhs)
{
    return lhs.red_   == rhs.red_
        && lhs.green_ == rhs.green_
        && lhs.blue_  == rhs.blue_;
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
    constexpr greyscale_colour()
      : shade_(0)
    {
    }

    constexpr explicit greyscale_colour(terminalpp::u8 shade)
      : shade_(shade)
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
    enum class type : terminalpp::u8
    {
        low, high, greyscale
    };

    constexpr colour()
      : colour(terminalpp::low_colour())
    {
    }

    constexpr colour(terminalpp::low_colour col)
      : low_colour_(std::move(col)),
        type_(type::low)
    {
    }

    constexpr colour(terminalpp::high_colour col)
      : high_colour_(std::move(col)),
        type_(type::high)
    {
    }

    constexpr colour(terminalpp::greyscale_colour col)
      : greyscale_colour_(std::move(col)),
        type_(type::greyscale)
    {
    }
    
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
/// \brief Stream operator for colours.
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, colour const &col);

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

//* =========================================================================
/// \brief Stream operator for attributes.
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, attribute const &attr);

}

#endif
