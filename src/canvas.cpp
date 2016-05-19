#include "terminalpp/canvas.hpp"

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
    return container.empty() ? nullptr : &*container.end();
}

}

// ==========================================================================
// COLUMN_PROXY::CONSTRUCTOR
// ==========================================================================
canvas::column_proxy::column_proxy(canvas &cvs, u32 column)
  : canvas_(cvs),
    column_(column)
{
}

// ==========================================================================
// COLUMN_PROXY::OPERATOR[]
// ==========================================================================
element &canvas::column_proxy::operator[](u32 row)
{
    return canvas_.get_element(column_, row);
}

// ==========================================================================
// CONST_COLUMN_PROXY::CONSTRUCTOR
// ==========================================================================
canvas::const_column_proxy::const_column_proxy(canvas const& cvs, u32 column)
  : canvas_(cvs),
    column_(column)
{
}

// ==========================================================================
// CONST_COLUMN_PROXY::OPERATOR[]
// ==========================================================================
element const& canvas::const_column_proxy::operator[](u32 row) const
{
    return canvas_.get_element(column_, row);
}

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
canvas::canvas(extent size)
  : size_(size)
{
    grid_.resize(size.width * size.height);
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
    std::vector<element> new_grid(size.width * size.height);
    auto min_width  = (std::min)(size.width, size_.width);
    auto min_height = (std::min)(size.height, size_.height);

    for (u32 row = 0; row < min_height; ++row)
    {
        for (u32 column = 0; column < min_width; ++column)
        {
            auto new_grid_pos = row * size.width + column;
            auto old_grid_pos = row * size_.width + column;

            new_grid[new_grid_pos] = grid_[old_grid_pos];
        }
    }

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
canvas::column_proxy canvas::operator[](u32 column)
{
    return column_proxy(*this, column);
}

// ==========================================================================
// OPERATOR[]
// ==========================================================================
canvas::const_column_proxy canvas::operator[](u32 column) const
{
    return const_column_proxy(*this, column);
}

// ==========================================================================
// SET_ELEMENT
// ==========================================================================
element& canvas::get_element(u32 column, u32 row)
{
    return grid_[row * size_.width + column];
}

// ==========================================================================
// GET_ELEMENT
// ==========================================================================
const element& canvas::get_element(u32 column, u32 row) const
{
    return grid_[row * size_.width + column];
}

// ==========================================================================
// GET_ELEMENT
// ==========================================================================
void canvas::set_element(u32 column, u32 row, const element& value)
{
    grid_[row * size_.width + column] = value;
}

}
