#pragma once

#include "terminalpp/core.hpp"

#include <iosfwd>

namespace terminalpp {

//* =========================================================================
/// \brief A class that represents a direction with distance in space
/// (a vector).
/// \par
/// A class that represents a direction in space, with width being the
/// extent in the horizontal axis, and height being the extent in the
/// vertical axis.
//* =========================================================================
struct TERMINALPP_EXPORT extent
{
    //* =====================================================================
    /// \brief Default Constructor
    /// \par
    /// Constructs an extent, leaving the width and height zeroed.
    //* =====================================================================
    constexpr extent() noexcept : width_(0), height_(0)
    {
    }

    //* =====================================================================
    /// \brief Constructor
    /// \par
    /// Constructs an extent with width and height being set to the passed-in
    /// arguments.
    //* =====================================================================
    constexpr extent(coordinate_type w, coordinate_type h) noexcept  // NOLINT
      : width_(w), height_(h)
    {
    }

    //* =====================================================================
    /// \brief Addition
    //* =====================================================================
    constexpr extent &operator+=(extent const &rhs) noexcept
    {
        width_ += rhs.width_;
        height_ += rhs.height_;
        return *this;
    }

    //* =====================================================================
    /// \brief Addition
    //* =====================================================================
    [[nodiscard]] constexpr friend auto operator+(
        extent lhs, extent const &rhs) noexcept
    {
        return lhs += rhs;
    }

    //* =====================================================================
    /// \brief Subtraction
    //* =====================================================================
    constexpr extent &operator-=(extent const &rhs) noexcept
    {
        width_ -= rhs.width_;
        height_ -= rhs.height_;
        return *this;
    }

    //* =====================================================================
    /// \brief Subtraction
    //* =====================================================================
    [[nodiscard]] constexpr friend auto operator-(
        extent lhs, extent const &rhs) noexcept
    {
        return lhs -= rhs;
    }

    //* =====================================================================
    /// \brief Relational operators for extents
    //* =====================================================================
    [[nodiscard]] constexpr friend auto operator<=>(
        extent const &lhs, extent const &rhs) noexcept = default;

    coordinate_type width_;
    coordinate_type height_;
};

//* =====================================================================
/// \brief Outputs the current state of the extent to a stream.
/// For example, "extent(35,49)"
//* =====================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, extent const &ext);

}  // namespace terminalpp
