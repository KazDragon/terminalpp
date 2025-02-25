#pragma once

#include "terminalpp/attribute.hpp"
#include "terminalpp/core.hpp"
#include "terminalpp/glyph.hpp"

#include <boost/container_hash/hash.hpp>

#include <iosfwd>
#include <utility>

namespace terminalpp {

//* =========================================================================
/// \brief A structure that represents the fundamental printable element of
/// a terminal screen, which comprises a glyph modified by a set of
/// attribute (such as colour, intensity, etc.)
//* =========================================================================
struct TERMINALPP_EXPORT element
{
    //* =====================================================================
    /// \brief Value Constructor
    //* =====================================================================
    constexpr element(  // NOLINT
        terminalpp::glyph gly = {},
        terminalpp::attribute attr = {}) noexcept
      : glyph_(std::move(gly)), attribute_(std::move(attr))
    {
    }

    //* =====================================================================
    /// \brief Char Constructor
    //* =====================================================================
    constexpr element(  // NOLINT
        byte ch,
        terminalpp::attribute attr = {}) noexcept
      : element(terminalpp::glyph(ch), attr)
    {
    }

    //* =====================================================================
    /// \brief Hash function
    //* =====================================================================
    [[nodiscard]] friend std::size_t hash_value(element const &elem) noexcept
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, elem.glyph_);
        boost::hash_combine(seed, elem.attribute_);

        return seed;
    }

    //* =====================================================================
    /// \brief Relational operators for elements
    //* =====================================================================
    [[nodiscard]] constexpr friend auto operator<=>(
        element const &lhs, element const &rhs) noexcept = default;

    terminalpp::glyph glyph_;
    terminalpp::attribute attribute_;
};

//* =========================================================================
/// \brief Streaming output operator for element.  Prints the text
/// equivalent of the element (e.g. "glyph[c],attribute[red]").
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, element const &elem);

}  // namespace terminalpp

#include "terminalpp/detail/element_udl.hpp"

namespace terminalpp {  // NOLINT
inline namespace literals {

inline constexpr element operator""_ete(char const *text, std::size_t len)
{
    element elem;
    std::span data{text, len};
    return detail::parse_element(data, elem);
}

}  // namespace literals
}  // namespace terminalpp

namespace std {

template <>
struct hash<terminalpp::element>
{
    using argument_type = terminalpp::element;
    using result_type = std::size_t;

    result_type operator()(argument_type const &elem) const noexcept
    {
        return hash_value(elem);
    }
};

}  // namespace std
