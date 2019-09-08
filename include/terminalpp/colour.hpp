#pragma once
#include "terminalpp/ansi/protocol.hpp"
#include <boost/operators.hpp>
#include <iosfwd>

namespace terminalpp {

//* =========================================================================
/// \brief Structure representing a normal ANSI 16-colour value
//* =========================================================================
struct low_colour
  : private boost::less_than_comparable<low_colour,
            boost::equality_comparable<low_colour>>
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
/// \brief Less-than operator for low_colours.
//* =========================================================================
constexpr bool operator<(low_colour const &lhs, low_colour const &rhs)
{
    return lhs.value_ < rhs.value_;
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
  : private boost::less_than_comparable<high_colour,
            boost::equality_comparable<high_colour>>
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
/// \brief Less-than operator for high_colours.
//* =========================================================================
constexpr bool operator<(high_colour const &lhs, high_colour const &rhs)
{
    return lhs.value_ < rhs.value_;
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
  : private boost::less_than_comparable<greyscale_colour,
            boost::equality_comparable<greyscale_colour>>
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
/// \brief Less-than operator for greyscale_colours.
//* =========================================================================
constexpr bool operator<(
    greyscale_colour const &lhs, greyscale_colour const &rhs)
{
    return lhs.shade_ < rhs.shade_;
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
  : private boost::less_than_comparable<colour,
            boost::equality_comparable<colour>>
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
/// \brief Less-than operator for colours.
//* =========================================================================
constexpr bool operator<(colour const &lhs, colour const &rhs)
{
    if (lhs.type_ < rhs.type_)
    {
        return true;
    }
    
    if (lhs.type_ == rhs.type_)
    {
        return lhs.type_ == colour::type::low
             ? lhs.low_colour_ < rhs.low_colour_
             : lhs.type_ == colour::type::high
             ? lhs.high_colour_ < rhs.high_colour_
             : lhs.type_ == colour::type::greyscale
             ? lhs.greyscale_colour_ < rhs.greyscale_colour_
             : false;
    }
    
    return false;
}

//* =========================================================================
/// \brief Streaming output operator for colours.  Prints the text equivalent
/// of the colour (e.g. "red", "#234", "#07", etc.)
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, colour const &col);

}
