#include "terminalpp/canvas_view.hpp"
#include "terminalpp/canvas.hpp"

namespace terminalpp {
    
// ==========================================================================
// ROW_PROXY::CONSTRUCTOR
// ==========================================================================
canvas_view::row_proxy::row_proxy(canvas_view& cvs, u32 column, u32 row)
  : canvas_(cvs),
    column_(column),
    row_(row)
{
}
    
// ==========================================================================
// ROW_PROXY::OPERATOR=
// ==========================================================================
canvas_view::row_proxy &canvas_view::row_proxy::operator=(
    canvas_view::row_proxy const &other)
{
    canvas_.set_element(column_, row_, other);
    return *this;
}

// ==========================================================================
// ROW_PROXY::OPERATOR=
// ==========================================================================
canvas_view::row_proxy &canvas_view::row_proxy::operator=(
    element const &value)
{
    canvas_.set_element(column_, row_, value);
    return *this;
}

// ==========================================================================
// ROW_PROXY::CONVERSION OPERATOR
// ==========================================================================
canvas_view::row_proxy::operator element &()
{
    return canvas_.get_element(column_, row_);
}

// ==========================================================================
// ROW_PROXY::CONVERSION OPERATOR
// ==========================================================================
canvas_view::row_proxy::operator element const &() const
{
    return canvas_.get_element(column_, row_);
}

// ==========================================================================
// COLUMN_PROXY::CONSTRUCTOR
// ==========================================================================
canvas_view::column_proxy::column_proxy(canvas_view &cvs, u32 column)
  : canvas_(cvs),
    column_(column)
{
}

// ==========================================================================
// COLUMN_PROXY::OPERATOR[]
// ==========================================================================
canvas_view::row_proxy canvas_view::column_proxy::operator[](u32 row)
{
    return canvas_view::row_proxy(canvas_, column_, row);
}

// ==========================================================================
// CONST_COLUMN_PROXY::CONSTRUCTOR
// ==========================================================================
canvas_view::const_column_proxy::const_column_proxy(
    canvas_view const &cvs, u32 column)
  : canvas_(cvs),
    column_(column)
{
}

// ==========================================================================
// CONST_COLUMN_PROXY::OPERATOR[]
// ==========================================================================
element const &canvas_view::const_column_proxy::operator[](u32 row) const
{
    return canvas_.get_element(column_, row);
}

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
canvas_view::canvas_view(canvas &cvs)
  : canvas_(cvs)
{
}

// ==========================================================================
// OFFSET_BY
// ==========================================================================
void canvas_view::offset_by(extent offset)
{
    offset_ += offset;
}

// ==========================================================================
// SIZE
// ==========================================================================
extent canvas_view::size() const
{
    return canvas_.size() - offset_;
}

// ==========================================================================
// OPERATOR[]
// ==========================================================================
canvas_view::column_proxy canvas_view::operator[](u32 column)
{
    return column_proxy(*this, column);
}

// ==========================================================================
// OPERATOR[]
// ==========================================================================
canvas_view::const_column_proxy canvas_view::operator[](u32 column) const
{
    return const_column_proxy(*this, column);
}

// ==========================================================================
// GET_ELEMENT
// ==========================================================================
element &canvas_view::get_element(u32 column, u32 row)
{
    return canvas_[column + offset_.width][row + offset_.height];
}

// ==========================================================================
// GET_ELEMENT
// ==========================================================================
element const &canvas_view::get_element(u32 column, u32 row) const
{
    return canvas_[column + offset_.width][row + offset_.height];
}

// ==========================================================================
// SET_ELEMENT
// ==========================================================================
void canvas_view::set_element(u32 column, u32 row, element const &value)
{
    canvas_[column + offset_.width][row + offset_.height] = value;
}

}