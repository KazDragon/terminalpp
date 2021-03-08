#pragma once

#include "terminalpp/core.hpp"
#include <boost/operators.hpp>
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
      : x_(0),
        y_(0)
    {
    }

    //* =====================================================================
    /// \brief Constructor
    /// \par
    /// Constructs a point from a passed in x co-ordinate and a passed in
    /// y co-ordinate.
    //* =====================================================================
    constexpr point(coordinate_type x, coordinate_type y)
      : x_(x),
        y_(y)
    {
    }

    //* =====================================================================
    /// \brief Addition
    //* =====================================================================
    constexpr point &operator+=(point const &rhs)
    {
        x_ += rhs.x_;
        y_ += rhs.y_;
        return *this;
    }

    //* =====================================================================
    /// \brief Subtraction
    //* =====================================================================
    constexpr point &operator-=(point const &rhs)
    {
        x_ -= rhs.x_;
        y_ -= rhs.y_;
        return *this;
    }

    //* =====================================================================
    /// \brief Less-than operator
    //* =====================================================================
    constexpr friend bool operator<(point const &lhs, point const &rhs)
    {
        // Note: reimplemented due to std::tie not being constexpr everywhere.
        return lhs.y_ < rhs.y_
            || (lhs.y_ == rhs.y_ && lhs.x_ < rhs.x_);
    }

    //* =====================================================================
    /// \brief Equality operator
    //* =====================================================================
    constexpr friend bool operator==(point const &lhs, point const &rhs)
    {
        return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_;
    }

    coordinate_type x_;
    coordinate_type y_;
};

//* =====================================================================
/// \brief Outputs the current state of the point to a stream.
/// For example, "point(35,49)"
//* =====================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, point const &pt);

}
