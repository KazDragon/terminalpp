#pragma once

#include "terminalpp/core.hpp"
#include <boost/operators.hpp>
#include <iosfwd>
#include <tuple>

namespace terminalpp {

//* =========================================================================
/// \brief A class that represents a position in space.
/// \par
/// A class that represents a position in space, where x is the co-ordinate
/// along the horizontal axis and y being the co-ordinate along the vertical
/// axis.
//* =========================================================================
struct point
  : private boost::less_than_comparable<point,
            boost::equality_comparable<point,
            boost::addable<point,
            boost::subtractable<point>>>>
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
    constexpr point(coordinate_type x_coordinate, coordinate_type y_coordinate)
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

    coordinate_type x;
    coordinate_type y;
};

// ==========================================================================
// OPERATOR<(POINT,POINT)
// ==========================================================================
constexpr bool operator<(point const &lhs, point const &rhs)
{
    return std::tie(lhs.y, lhs.x) < std::tie(rhs.y, rhs.x);
}

// ==========================================================================
// OPERATOR==(POINT,POINT)
// ==========================================================================
constexpr bool operator==(point const &lhs, point const &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

//* =====================================================================
/// \brief Outputs the current state of the point to a stream.
/// For example, "point(35,49)"
//* =====================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, point const &pt);

}
