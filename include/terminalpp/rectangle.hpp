#pragma once

#include "terminalpp/detail/export.hpp"
#include "terminalpp/extent.hpp"
#include "terminalpp/point.hpp"

#include <boost/operators.hpp>

#include <iosfwd>

namespace terminalpp {

//* =========================================================================
/// \brief A class that represents a rectangle in space.
//* =========================================================================
struct TERMINALPP_EXPORT rectangle
  : private boost::
        less_than_comparable<rectangle, boost::equality_comparable<rectangle>>
{
    //* =====================================================================
    /// \brief Default Constructor
    /// \par
    /// Constructs the rectangle, leaving the origin and size uninitialized.
    //* =====================================================================
    constexpr rectangle() = default;

    //* =====================================================================
    /// \brief Constructor
    /// \par
    /// Constructs the rectangle, using the specified origin and size.
    //* =====================================================================
    constexpr rectangle(terminalpp::point origin, terminalpp::extent size)
      : origin_(origin), size_(size)
    {
    }

    //* =====================================================================
    /// \brief Less-than operator
    //* =====================================================================
    constexpr friend bool operator<(rectangle const &lhs, rectangle const &rhs)
    {
        return lhs.origin_ < rhs.origin_
            || (lhs.origin_ == rhs.origin_ && lhs.size_ < rhs.size_);
    }

    //* =====================================================================
    /// \brief Equality operator
    //* =====================================================================
    constexpr friend bool operator==(rectangle const &lhs, rectangle const &rhs)
    {
        return lhs.origin_ == rhs.origin_ && lhs.size_ == rhs.size_;
    }

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
