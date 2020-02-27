#pragma once

#include "terminalpp/detail/export.hpp"
#include "terminalpp/point.hpp"
#include "terminalpp/extent.hpp"
#include <iosfwd>

namespace terminalpp {

//* =========================================================================
/// \brief A class that represents a rectangle in space.
//* =========================================================================
struct rectangle
{
    //* =====================================================================
    /// \brief Default Constructor
    /// \par
    /// Constructs the rectangle, leaving the origin and size uninitialised.
    //* =====================================================================
    constexpr rectangle() = default;

    //* =====================================================================
    /// \brief Constructor
    /// \par
    /// Constructs the rectangle, using the specified origin and size.
    //* =====================================================================
    constexpr rectangle(terminalpp::point org, terminalpp::extent sz)
      : origin(org),
        size(sz)
    {
    }

    /// \brief The origin (top-left point) of the rectangle.
    terminalpp::point  origin;

    /// \brief The size (amount the rectangle extends right and down) of
    /// the rectangle.
    terminalpp::extent size;
};

// ==========================================================================
// OPERATOR==(RECTANGLE,RECTANGLE)
// ==========================================================================
constexpr bool operator==(rectangle const &lhs, rectangle const &rhs)
{
    return lhs.origin == rhs.origin && lhs.size == rhs.size;
}

// ==========================================================================
// OPERATOR!=(RECTANGLE,RECTANGLE)
// ==========================================================================
constexpr bool operator!=(rectangle const &lhs, rectangle const &rhs)
{
    return !(lhs == rhs);
}

//* =====================================================================
/// \brief Outputs the current state of the point to a stream.
/// For example, "rectangle(point(35,49), extent(32,90))"
//* =====================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, rectangle const &pt);

}
