#include "terminalpp/canvas.hpp"

namespace terminalpp {

namespace {

template <class Container>
auto begin_pointer(Container &&container)
{
    return container.empty() ? nullptr : &*container.begin();
}

template <class Container>
auto end_pointer(Container &&container)
{
    return container.empty() ? nullptr : &*container.end();
}

}

// ==========================================================================
// COLUMN_PROXY::CONSTRUCTOR
// ==========================================================================
canvas::column_proxy::column_proxy(canvas &cvs, s32 column)
  : canvas_(cvs),
    column_(column)
{
}

// ==========================================================================
// COLUMN_PROXY::OPERATOR[]
// ==========================================================================
canvas::row_proxy canvas::column_proxy::operator[](s32 row)
{
    return canvas::row_proxy(canvas_, column_, row);
}

// ==========================================================================
// CONST_COLUMN_PROXY::CONSTRUCTOR
// ==========================================================================
canvas::const_column_proxy::const_column_proxy(canvas const& cvs, s32 column)
  : canvas_(cvs),
    column_(column)
{
}

// ==========================================================================
// CONST_COLUMN_PROXY::OPERATOR[]
// ==========================================================================
element const& canvas::const_column_proxy::operator[](s32 row) const
{
    return canvas_.get_element(column_, row);
}

// ==========================================================================
// ROW_PROXY::CONSTRUCTOR
// ==========================================================================
canvas::row_proxy::row_proxy(canvas& cvs, s32 column, s32 row)
  : canvas_(cvs),
    column_(column),
    row_(row)
{
}

// ==========================================================================
// ROW_PROXY::OPERATOR=
// ==========================================================================
void canvas::row_proxy::operator=(element const &value)
{
    canvas_.set_element(column_, row_, value);
}

// ==========================================================================
// ROW::CONVERSION OPERATOR
// ==========================================================================
canvas::row_proxy::operator element &()
{
    return canvas_.get_element(column_, row_);
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
canvas::column_proxy canvas::operator[](s32 column)
{
    return column_proxy(*this, column);
}

// ==========================================================================
// OPERATOR[]
// ==========================================================================
canvas::const_column_proxy canvas::operator[](s32 column) const
{
    return const_column_proxy(*this, column);
}

// ==========================================================================
// SET_ELEMENT
// ==========================================================================
element& canvas::get_element(s32 column, s32 row)
{
    return grid_[row * size_.width + column];
}

// ==========================================================================
// GET_ELEMENT
// ==========================================================================
const element& canvas::get_element(s32 column, s32 row) const
{
    return grid_[row * size_.width + column];
}

// ==========================================================================
// GET_ELEMENT
// ==========================================================================
void canvas::set_element(s32 column, s32 row, const element& value)
{
    grid_[row * size_.width + column] = value;
}

}
