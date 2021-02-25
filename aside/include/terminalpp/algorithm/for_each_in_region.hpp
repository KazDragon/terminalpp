#pragma once

#include "terminalpp/element.hpp"
#include "terminalpp/rectangle.hpp"
#include <type_traits>
#include <utility>

namespace terminalpp {

//* =========================================================================
/// \brief Iterate a 2D array in row-major order, providing indexed access
/// to each element therein.
///
/// \tparam TwoDimensionalContainer A container where @c container[x][y] is
///         a valid expression that yields an element.
/// \tparam IndexedElementFunction A function of the form @c
///         void(element &, x_coordinate, y_coordinate) or @c
///         void(element const &, x_coordinate, y_coordinate) where @c element
///         is a type inside the container and x_coordinate and y_coordinate
///         are index types for accessing that element.  The constness of
///         the element must be convertible from the elements in the 
///         container (i.e. a function taking non-const will not be callable)
///         when passed a const canvas).
//* =========================================================================
template <
    typename TwoDimensionalContainer,
    typename IndexedElementFunction
>
void for_each_in_region(
    TwoDimensionalContainer &&container,
    rectangle const &region,
    IndexedElementFunction &&callable)
{
    using x_coordinate = 
        typename std::remove_cv<
            typename std::remove_reference<TwoDimensionalContainer>::type
        >::type::size_type;
    
    using y_coordinate =
        typename std::remove_cv<
            typename std::remove_reference<
                decltype(container[std::declval<x_coordinate>()])
            >::type
        >::type::size_type;

    static_assert(std::is_same<
        terminalpp::element,
        typename std::remove_cv<
            typename std::remove_reference<
                decltype(container[std::declval<x_coordinate>()][std::declval<y_coordinate>()])
            >::type
        >::type>::value, "container[x][y] must yield an element");

    for (auto row = region.origin.y; 
         row < region.origin.y + region.size.height; 
         ++row)
    {
        for (auto column = region.origin.x; 
             column < region.origin.x + region.size.width; 
             ++column)
        {
            callable(container[column][row], column, row);
        }
    }
}

}