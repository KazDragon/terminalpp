#pragma once

#include "terminalpp/detail/export.hpp"
#include "terminalpp/extent.hpp"
#include "terminalpp/point.hpp"

#include <iosfwd>

namespace terminalpp {

//* =========================================================================
/// \brief A class that represents a rectangle in space.
//* =========================================================================
struct TERMINALPP_EXPORT rectangle
{
    //* =====================================================================
    /// \brief Default Constructor
    /// \par
    /// Constructs the rectangle, leaving the origin and size uninitialized.
    //* =====================================================================
    constexpr rectangle() noexcept = default;

    //* =====================================================================
    /// \brief Constructor
    /// \par
    /// Constructs the rectangle, using the specified origin and size.
    //* =====================================================================
    constexpr rectangle(
        terminalpp::point origin, terminalpp::extent size) noexcept
      : origin_(origin), size_(size)
    {
    }

    //* =====================================================================
    /// \brief Relational operators for rectangles
    //* =====================================================================
    [[nodiscard]] constexpr friend auto operator<=>(
        rectangle const &lhs, rectangle const &rhs) noexcept = default;

    /// \brief The origin (top-left point) of the rectangle.
    terminalpp::point origin_;

    /// \brief The size (amount the rectangle extends right and down) of
    /// the rectangle.
    terminalpp::extent size_;
};

//* =====================================================================
/// \brief Outputs the current state of the point to a stream.
/// For example, "rectangle(point(35,49), extent(32,90))"
//* =====================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, rectangle const &rect);

}  // namespace terminalpp
