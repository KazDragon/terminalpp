#pragma once

#include "terminalpp/core.hpp"

#include <boost/operators.hpp>

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
  : private boost::less_than_comparable<
        extent,
        boost::equality_comparable<
            extent,
            boost::addable<extent, boost::subtractable<extent>>>>
{
    //* =====================================================================
    /// \brief Default Constructor
    /// \par
    /// Constructs an extent, leaving the width and height zeroed.
    //* =====================================================================
    constexpr extent() : width_(0), height_(0)
    {
    }

    //* =====================================================================
    /// \brief Constructor
    /// \par
    /// Constructs an extent with width and height being set to the passed-in
    /// arguments.
    //* =====================================================================
    constexpr extent(coordinate_type w, coordinate_type h)
      : width_(w), height_(h)
    {
    }

    //* =====================================================================
    /// \brief Addition
    //* =====================================================================
    constexpr extent &operator+=(extent const &rhs)
    {
        width_ += rhs.width_;
        height_ += rhs.height_;
        return *this;
    }

    //* =====================================================================
    /// \brief Subtraction
    //* =====================================================================
    constexpr extent &operator-=(extent const &rhs)
    {
        width_ -= rhs.width_;
        height_ -= rhs.height_;
        return *this;
    }

    // ======================================================================
    // OPERATOR<(EXTENT,EXTENT)
    // ======================================================================
    constexpr friend bool operator<(extent const &lhs, extent const &rhs)
    {
        return lhs.width_ < rhs.width_
            || (lhs.width_ == rhs.width_ && lhs.height_ < rhs.height_);
    }

    // ======================================================================
    // OPERATOR==(EXTENT,EXTENT)
    // ======================================================================
    constexpr friend bool operator==(extent const &lhs, extent const &rhs)
    {
        return lhs.width_ == rhs.width_ && lhs.height_ == rhs.height_;
    }

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
