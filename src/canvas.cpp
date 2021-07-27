#include "terminalpp/canvas.hpp"
#include "terminalpp/algorithm/for_each_in_region.hpp"

namespace terminalpp {

namespace {

// ==========================================================================
// BEGIN_POINTER
// ==========================================================================
template <class Container>
auto begin_pointer(Container &&container)
{
    return container.empty() ? nullptr : &*container.begin();
}

// ==========================================================================
// END_POINTER
// ==========================================================================
template <class Container>
auto end_pointer(Container &&container)
{
    return container.empty() ? nullptr : &*container.begin() + container.size();
}

}

// ==========================================================================
// COLUMN_PROXY::CONSTRUCTOR
// ==========================================================================
canvas::column_proxy::column_proxy(canvas &cvs, coordinate_type column)
  : canvas_(cvs),
    column_(column)
{
}

// ==========================================================================
// COLUMN_PROXY::OPERATOR[]
// ==========================================================================
element &canvas::column_proxy::operator[](coordinate_type row)
{
    return canvas_.get_element(column_, row);
}

// ==========================================================================
// CONST_COLUMN_PROXY::CONSTRUCTOR
// ==========================================================================
canvas::const_column_proxy::const_column_proxy(
    canvas const& cvs, coordinate_type column)
  : canvas_(cvs),
    column_(column)
{
}

// ==========================================================================
// CONST_COLUMN_PROXY::OPERATOR[]
// ==========================================================================
element const& canvas::const_column_proxy::operator[](
    coordinate_type row) const
{
    return canvas_.get_element(column_, row);
}

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
canvas::canvas(extent size)
  : size_(size)
{
    grid_.resize(std::vector<element>::size_type(size.width_ * size.height_));
}

// ==========================================================================
// SIZE
// ==========================================================================
extent canvas::size() const
{
    return size_;
}

// ==========================================================================
// RESIZE
// ==========================================================================
void canvas::resize(extent const &size)
{
    std::vector<element> new_grid(std::vector<element>::size_type(
        size.width_ * size.height_));

    auto min_width  = (std::min)(size.width_, size_.width_);
    auto min_height = (std::min)(size.height_, size_.height_);

    for_each_in_region(
        *this, {{}, {min_width, min_height}},
        [&size, &new_grid](
            element const &elem, coordinate_type column, coordinate_type row)
        {
             auto const new_grid_pos = std::vector<element>::size_type(
                 row * size.width_ + column);
             new_grid[new_grid_pos] = elem;
        });

    size_ = size;
    grid_.swap(new_grid);
}

// ==========================================================================
// BEGIN
// ==========================================================================
canvas::iterator canvas::begin()
{
    return begin_pointer(grid_);
}

// ==========================================================================
// BEGIN
// ==========================================================================
canvas::const_iterator canvas::begin() const
{
    return begin_pointer(grid_);
}

// ==========================================================================
// END
// ==========================================================================
canvas::iterator canvas::end()
{
    return end_pointer(grid_);
}

// ==========================================================================
// END
// ==========================================================================
canvas::const_iterator canvas::end() const
{
    return end_pointer(grid_);
}

// ==========================================================================
// OPERATOR[]
// ==========================================================================
canvas::column_proxy canvas::operator[](coordinate_type column)
{
    return column_proxy(*this, column);
}

// ==========================================================================
// OPERATOR[]
// ==========================================================================
canvas::const_column_proxy canvas::operator[](coordinate_type column) const
{
    return const_column_proxy(*this, column);
}

// ==========================================================================
// GET_ELEMENT
// ==========================================================================
element& canvas::get_element(coordinate_type column, coordinate_type row)
{
    return grid_[std::vector<element>::size_type(
        row * size_.width_ + column
    )];
}

// ==========================================================================
// GET_ELEMENT
// ==========================================================================
const element& canvas::get_element(
    coordinate_type column, coordinate_type row) const
{
    return grid_[std::vector<element>::size_type(
        row * size_.width_ + column
    )];
}

}
