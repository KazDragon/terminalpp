#pragma once

#include "terminalpp/core.hpp"
#include "terminalpp/element.hpp"
#include "terminalpp/rectangle.hpp"

#include <concepts>  // IWYU pragma: keep

namespace terminalpp {

template <typename TwoDimensionalContainer>
concept element_container = requires(TwoDimensionalContainer tdc) {
    {
        tdc[terminalpp::coordinate_type{}][terminalpp::coordinate_type{}]
    } -> std::convertible_to<terminalpp::element>;
};

//* =========================================================================
/// \brief Iterate a 2D array in row-major order, calling the passed
/// function on each element.
//* =========================================================================
void for_each_in_region(
    element_container auto &&container,
    rectangle const &region,
    std::invocable<element &, coordinate_type, coordinate_type> auto &&callable)
{
    for (auto row = region.origin_.y_;
         row < region.origin_.y_ + region.size_.height_;
         ++row)
    {
        for (auto column = region.origin_.x_;
             column < region.origin_.x_ + region.size_.width_;
             ++column)
        {
            callable(container[column][row], column, row);
        }
    }
}

}  // namespace terminalpp