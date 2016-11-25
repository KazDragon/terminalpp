#pragma once

#include "terminalpp/core.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief A class that represents a position in space.
/// \par
/// A class that represents a position in space, where x is the co-ordinate
/// along the horizontal axis and y being the co-ordinate along the vertical
/// axis.
//* =========================================================================
struct point
{
    //* =====================================================================
    /// \brief Default Constructor
    /// \par
    /// Constructs a point, leaving the values uninitialised.
    //* =====================================================================
    constexpr point()
      : x(0),
        y(0)
    {
    }

    //* =====================================================================
    /// \brief Constructor
    /// \par
    /// Constructs a point from a passed in x co-ordinate and a passed in
    /// y co-ordinate.
    //* =====================================================================
    constexpr point(s32 x_coordinate, s32 y_coordinate)
      : x(x_coordinate),
        y(y_coordinate)
    {
    }

    //* =====================================================================
    /// \brief Addition
    //* =====================================================================
    constexpr point &operator+=(point const &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    //* =====================================================================
    /// \brief Subtraction
    //* =====================================================================
    constexpr point &operator-=(point const &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    s32 x;
    s32 y;
};

// ==========================================================================
// OPERATOR==(POINT,POINT)
// ==========================================================================
constexpr bool operator==(point const &lhs, point const &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

// ==========================================================================
// OPERATOR!=(POINT,POINT)
// ==========================================================================
constexpr bool operator!=(point const &lhs, point const &rhs)
{
    return !(lhs == rhs);
}

// ==========================================================================
// OPERATOR+(POINT,POINT)
// ==========================================================================
constexpr point operator+(point lhs, point const &rhs)
{
    return lhs += rhs;
}

// ==========================================================================
// OPERATOR-(POINT,POINT)
// ==========================================================================
constexpr point operator-(point lhs, point const &rhs)
{
    return lhs -= rhs;
}

}
