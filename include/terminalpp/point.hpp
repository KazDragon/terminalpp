#pragma once

#include "terminalpp/core.hpp"

#include <iosfwd>

namespace terminalpp {

//* =========================================================================
/// \brief A class that represents a position in space.
/// \par
/// A class that represents a position in space, where x is the co-ordinate
/// along the horizontal axis and y being the co-ordinate along the vertical
/// axis.
//* =========================================================================
struct TERMINALPP_EXPORT point
{
    //* =====================================================================
    /// \brief Default Constructor
    /// \par
    /// Constructs a point, leaving the values uninitialized.
    //* =====================================================================
    constexpr point() : y_(0), x_(0)
    {
    }

    //* =====================================================================
    /// \brief Constructor
    /// \par
    /// Constructs a point from a passed in x co-ordinate and a passed in
    /// y co-ordinate.
    //* =====================================================================
    constexpr point(coordinate_type x, coordinate_type y) noexcept  // NOLINT
      : y_(y), x_(x)
    {
    }

    //* =====================================================================
    /// \brief Addition
    //* =====================================================================
    constexpr point &operator+=(point const &rhs) noexcept
    {
        x_ += rhs.x_;
        y_ += rhs.y_;
        return *this;
    }

    //* =====================================================================
    /// \brief Addition
    //* =====================================================================
    [[nodiscard]] constexpr friend auto operator+(
        point lhs, point const &rhs) noexcept
    {
        return lhs += rhs;
    }

    //* =====================================================================
    /// \brief Subtraction
    //* =====================================================================
    constexpr point &operator-=(point const &rhs) noexcept
    {
        x_ -= rhs.x_;
        y_ -= rhs.y_;
        return *this;
    }

    //* =====================================================================
    /// \brief Subtraction
    //* =====================================================================
    [[nodiscard]] constexpr friend auto operator-(
        point lhs, point const &rhs) noexcept
    {
        return lhs -= rhs;
    }

    //* =====================================================================
    /// \brief Relational operators for points
    //* =====================================================================
    [[nodiscard]] constexpr friend auto operator<=>(
        point const &lhs, point const &rhs) noexcept = default;

    coordinate_type y_;
    coordinate_type x_;
};

//* =====================================================================
/// \brief Outputs the current state of the point to a stream.
/// For example, "point(35,49)"
//* =====================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, point const &pt);

}  // namespace terminalpp
