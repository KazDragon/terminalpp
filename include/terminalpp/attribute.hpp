#pragma once

#include "terminalpp/colour.hpp"
#include "terminalpp/effect.hpp"

#include <boost/container_hash/hash.hpp>

#include <iosfwd>

namespace terminalpp {

//* =========================================================================
/// \brief A structure that carries around the presentation attributes of
/// an ANSI element.
//* =========================================================================
struct TERMINALPP_EXPORT attribute
{
    //* =====================================================================
    /// \brief Hash function
    //* =====================================================================
    [[nodiscard]] friend std::size_t hash_value(attribute const &attr) noexcept
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

    //* =====================================================================
    /// \brief Relational operators for attributes
    //* =====================================================================
    [[nodiscard]] constexpr friend auto operator<=>(
        attribute const &lhs, attribute const &rhs) noexcept = default;

    // Graphics Attributes
    colour foreground_colour_;
    colour background_colour_;
    intensity intensity_;
    underlining underlining_;
    polarity polarity_;
    blinking blinking_;
};

//* =========================================================================
/// \brief Streaming output operator for attribute.  Prints the text
/// equivalent of the attribute (e.g. "foreground_colour[red],bold")
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, attribute const &attr);

}  // namespace terminalpp

namespace std {

template <>
struct hash<terminalpp::attribute>
{
    using argument_type = terminalpp::attribute;
    using result_type = std::size_t;

    [[nodiscard]] result_type operator()(
        argument_type const &attr) const noexcept
    {
        return hash_value(attr);
    }
};

}  // namespace std
