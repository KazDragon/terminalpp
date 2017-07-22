#pragma once

#include "terminalpp/core.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief A class that represents a direction with distance in space
/// (a vector).
/// \par
/// A class that represents a direction in space, with width being the
/// extent in the horizontal axis, and height being the extent in the
/// vertical axis.
//* =========================================================================
struct extent
{
    using dimension_type = std::int32_t;

    //* =====================================================================
    /// \brief Default Constructor
    /// \par
    /// Constructs an extent, leaving the width and height zeroed.
    //* =====================================================================
    constexpr extent()
      : width(0),
        height(0)
    {
    }

    //* =====================================================================
    /// \brief Constructor
    /// \par
    /// Constructs an extent with width and height being set to the passed-in
    /// arguments.
    //* =====================================================================
    constexpr extent(dimension_type w, dimension_type h)
      : width(w),
        height(h)
    {
    }

    //* =====================================================================
    /// \brief Addition
    //* =====================================================================
    constexpr extent &operator+=(extent const &rhs)
    {
        width  += rhs.width;
        height += rhs.height;
        return *this;
    }

    //* =====================================================================
    /// \brief Subtraction
    //* =====================================================================
    constexpr extent &operator-=(extent const &rhs)
    {
        width  -= rhs.width;
        height -= rhs.height;
        return *this;
    }

    dimension_type width;
    dimension_type height;
};

// ==========================================================================
// OPERATOR==(EXTENT,EXTENT)
// ==========================================================================
constexpr bool operator==(extent const &lhs, extent const &rhs)
{
    return lhs.width == rhs.width && lhs.height == rhs.height;
}

// ==========================================================================
// OPERATOR!=(EXTENT,EXTENT)
// ==========================================================================
constexpr bool operator!=(extent const &lhs, extent const &rhs)
{
    return !(lhs == rhs);
}

// ==========================================================================
// OPERATOR+(EXTENT,EXTENT)
// ==========================================================================
constexpr extent operator+(extent lhs, extent const &rhs)
{
    return lhs += rhs;
}

// ==========================================================================
// OPERATOR-(EXTENT,EXTENT)
// ==========================================================================
constexpr extent operator-(extent lhs, extent const &rhs)
{
    return lhs -= rhs;
}

}
