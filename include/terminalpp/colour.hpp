#pragma once

#include "terminalpp/graphics.hpp"

#include <boost/container_hash/hash.hpp>

#include <iosfwd>
#include <variant>

namespace terminalpp {

//* =========================================================================
/// \brief Structure representing a normal ANSI 16-colour value
//* =========================================================================
struct TERMINALPP_EXPORT low_colour
{
    //* =====================================================================
    /// \brief Constructs a low_colour with the "default" colour value.
    //* =====================================================================
    constexpr low_colour() noexcept
      : low_colour(terminalpp::graphics::colour::default_)
    {
    }

    //* =====================================================================
    /// \brief Constructs a low_colour from the passed-in ANSI colour.
    //* =====================================================================
    constexpr low_colour(  // NOLINT
        terminalpp::graphics::colour colour) noexcept
      : value_(colour){};

    //* =====================================================================
    /// \brief Hash function
    //* =====================================================================
    [[nodiscard]] friend std::size_t hash_value(low_colour const &col) noexcept
    {
        std::size_t seed = 0;
        boost::hash_combine(
            seed,
            static_cast<std::underlying_type_t<decltype(col.value_)>>(
                col.value_));
        return seed;
    }

    //* =====================================================================
    /// \brief Comparison operators for low colours
    //* =====================================================================
    [[nodiscard]] constexpr friend auto operator<=>(
        low_colour const &lhs, low_colour const &rhs) noexcept = default;

    terminalpp::graphics::colour value_;
};

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
struct TERMINALPP_EXPORT high_colour
{
    //* =====================================================================
    /// \brief Default constructs a high-colour with the value of pure black.
    //* =====================================================================
    constexpr high_colour() noexcept : high_colour(0, 0, 0)
    {
    }

    //* =====================================================================
    /// \brief Constructs a high_colour from the passed-in RGB values, each
    /// of which should be in the range 0-5.
    //* =====================================================================
    constexpr high_colour(byte red, byte green, byte blue) noexcept
      : value_(ansi::graphics::encode_high_components(red, green, blue))
    {
    }

    //* =====================================================================
    /// \brief Hash function
    //* =====================================================================
    [[nodiscard]] friend std::size_t hash_value(high_colour const &col) noexcept
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, col.value_);
        return seed;
    }

    //* =====================================================================
    /// \brief Comparison operators for high colours
    //* =====================================================================
    [[nodiscard]] constexpr friend auto operator<=>(
        high_colour const &lhs, high_colour const &rhs) noexcept = default;

    byte value_;
};

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
struct TERMINALPP_EXPORT greyscale_colour
{
    //* =====================================================================
    /// \brief Default constructs a greyscale value with the darkest
    /// available grey.
    //* =====================================================================
    constexpr greyscale_colour() noexcept : shade_(0)
    {
    }

    //* =====================================================================
    /// \brief Constructs a greyscale value from the given shade, which
    /// should be in the range 0-23.
    //* =====================================================================
    constexpr explicit greyscale_colour(byte shade) noexcept
      : shade_(ansi::graphics::encode_greyscale_component(shade))
    {
    }

    //* =====================================================================
    /// \brief Hash function
    //* =====================================================================
    [[nodiscard]] friend std::size_t hash_value(
        greyscale_colour const &col) noexcept
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, col.shade_);
        return seed;
    }

    //* =====================================================================
    /// \brief Comparison operators for greyscale colours
    //* =====================================================================
    [[nodiscard]] constexpr friend auto operator<=>(
        greyscale_colour const &lhs,
        greyscale_colour const &rhs) noexcept = default;

    byte shade_;
};

//* =========================================================================
/// \brief Streaming output operator for greyscale_colours.  Prints the text
/// equivalent of the colour (e.g. #22, #00, etc.)
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, greyscale_colour const &col);

//* =========================================================================
/// \brief Structure representing the ~16 million colours codes of the
/// true colour palette.
//* =========================================================================
struct TERMINALPP_EXPORT true_colour
{
    //* =====================================================================
    /// \brief Default constructor constructs a true colour value that
    /// represents black.
    //* =====================================================================
    constexpr true_colour() noexcept : true_colour(0, 0, 0)
    {
    }

    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    constexpr true_colour(
        byte const red, byte const green, byte const blue) noexcept  // NOLINT
      : red_(red), green_(green), blue_(blue)
    {
    }

    //* =====================================================================
    /// \brief Hash function
    //* =====================================================================
    [[nodiscard]] friend std::size_t hash_value(true_colour const &col) noexcept
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, col.red_);
        boost::hash_combine(seed, col.green_);
        boost::hash_combine(seed, col.blue_);
        return seed;
    }

    //* =====================================================================
    /// \brief Comparison operators for true colours
    //* =====================================================================
    [[nodiscard]] constexpr friend auto operator<=>(
        true_colour const &lhs, true_colour const &rhs) noexcept = default;

    byte red_;
    byte green_;
    byte blue_;
};

//* =========================================================================
/// \brief Streaming output operator for true_colours.  Prints the hex
/// code of the colour (e.g. #AA00AA, etc.)
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, true_colour const &col);

//* =========================================================================
/// \brief Structure representing a sum type of the available colour styles.
//* =========================================================================
struct TERMINALPP_EXPORT colour
{
    //* =====================================================================
    /// \brief Default constructs the colour with the "default" ANSI colour.
    //* =====================================================================
    constexpr colour() noexcept : colour{terminalpp::low_colour()}
    {
    }

    //* =====================================================================
    /// \brief Constructs a colour with the passed low_colour value.
    //* =====================================================================
    constexpr colour(terminalpp::low_colour col) noexcept  // NOLINT
      : value_{std::move(col)}
    {
    }

    //* =====================================================================
    /// \brief Constructs a colour from an ANSI graphics low colour.
    //* =====================================================================
    constexpr colour(terminalpp::graphics::colour col) noexcept  // NOLINT
      : colour{terminalpp::low_colour(col)}
    {
    }

    //* =====================================================================
    /// \brief Constructs a colour with the passed high_colour value.
    //* =====================================================================
    constexpr colour(terminalpp::high_colour col) noexcept  // NOLINT
      : value_{high_colour{std::move(col)}}
    {
    }

    //* =====================================================================
    /// \brief Constructs a colour with the passed greyscale_colour value.
    //* =====================================================================
    constexpr colour(terminalpp::greyscale_colour col) noexcept  // NOLINT
      : value_{greyscale_colour{std::move(col)}}
    {
    }

    //* =====================================================================
    /// \brief Constructs a colour with the passed true_colour value.
    //* =====================================================================
    constexpr colour(terminalpp::true_colour col) noexcept  // NOLINT
      : value_{true_colour{std::move(col)}}
    {
    }

    //* =====================================================================
    /// \brief Hash function
    //* =====================================================================
    [[nodiscard]] friend std::size_t hash_value(colour const &col) noexcept
    {
        return std::visit(
            [](auto const &val) { return hash_value(val); }, col.value_);
    }

    //* =====================================================================
    /// \brief Comparison operators for colours
    //* =====================================================================
    [[nodiscard]] constexpr friend auto operator<=>(
        colour const &lhs, colour const &rhs) noexcept = default;

    std::variant<low_colour, high_colour, greyscale_colour, true_colour> value_;
};

//* =========================================================================
/// \brief Streaming output operator for colours.  Prints the text equivalent
/// of the colour (e.g. "red", "#234", "#07", etc.)
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, colour const &col);

}  // namespace terminalpp

namespace std {

template <>
struct hash<terminalpp::low_colour>
{
    using argument_type = terminalpp::low_colour;
    using result_type = std::size_t;

    [[nodiscard]] result_type operator()(
        argument_type const &col) const noexcept
    {
        return hash_value(col);
    }
};

template <>
struct hash<terminalpp::high_colour>
{
    using argument_type = terminalpp::high_colour;
    using result_type = std::size_t;

    [[nodiscard]] result_type operator()(
        argument_type const &col) const noexcept
    {
        return hash_value(col);
    }
};

template <>
struct hash<terminalpp::greyscale_colour>
{
    using argument_type = terminalpp::greyscale_colour;
    using result_type = std::size_t;

    [[nodiscard]] result_type operator()(
        argument_type const &col) const noexcept
    {
        return hash_value(col);
    }
};

template <>
struct hash<terminalpp::true_colour>
{
    using argument_type = terminalpp::true_colour;
    using result_type = std::size_t;

    [[nodiscard]] result_type operator()(
        argument_type const &col) const noexcept
    {
        return hash_value(col);
    }
};

template <>
struct hash<terminalpp::colour>
{
    using argument_type = terminalpp::colour;
    using result_type = std::size_t;

    [[nodiscard]] result_type operator()(
        argument_type const &col) const noexcept
    {
        return hash_value(col);
    }
};

}  // namespace std
