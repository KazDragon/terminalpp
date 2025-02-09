#pragma once

#include "terminalpp/element.hpp"
#include "terminalpp/extent.hpp"

#include <vector>

namespace terminalpp {

//* =========================================================================
/// \brief A class representing a grid onto which elements can be painted.
///
/// \par Usage
/// The grid is formed from a contiguous block of memory.  Position [0,0]
/// represents the top left of the grid, and it proceeds in a left-to-right
/// manner first, then top-to-bottom.
//* =========================================================================
class TERMINALPP_EXPORT canvas
{
public:
    using size_type = coordinate_type;
    using iterator = element *;
    using const_iterator = element const *;

    //* =====================================================================
    /// \brief A proxy into a column of elements on the canvas
    //* =====================================================================
    class TERMINALPP_EXPORT column_proxy
    {
    public:
        using size_type = coordinate_type;

        // ==================================================================
        // CONSTRUCTOR
        // ==================================================================
        column_proxy(canvas &cvs, size_type column);

        // ==================================================================
        // OPERATOR[]
        // ==================================================================
        [[nodiscard]] element &operator[](size_type row);

    private:
        canvas &canvas_;
        size_type column_;
    };

    //* =====================================================================
    /// \brief A constant proxy into a column of elements on the canvas
    //* =====================================================================
    class TERMINALPP_EXPORT const_column_proxy
    {
    public:
        using size_type = coordinate_type;

        // ==================================================================
        // CONSTRUCTOR
        // ==================================================================
        const_column_proxy(canvas const &cvs, size_type column);

        // ==================================================================
        // OPERATOR[]
        // ==================================================================
        [[nodiscard]] element const &operator[](coordinate_type row) const;

    private:
        canvas const &canvas_;
        size_type column_;
    };

    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    explicit canvas(extent size);

    //* =====================================================================
    /// \brief Returns the size of the canvas.
    //* =====================================================================
    [[nodiscard]] extent size() const;

    //* =====================================================================
    /// \brief Resizes the canvas to the specified extent.  Content that would
    /// fit in the new size remains as it was, otherwise it is truncated.
    //* =====================================================================
    void resize(extent const &size);

    //* =====================================================================
    /// \brief Returns pointer to the top-left element.
    //* =====================================================================
    [[nodiscard]] iterator begin();

    //* =====================================================================
    /// \brief Returns pointer to the top-left element.
    //* =====================================================================
    [[nodiscard]] const_iterator begin() const;

    //* =====================================================================
    /// \brief Returns one-past-the-end of the canvas.
    //* =====================================================================
    [[nodiscard]] iterator end();

    //* =====================================================================
    /// \brief Returns one-past-the-end of the canvas.
    //* =====================================================================
    [[nodiscard]] const_iterator end() const;

    //* =====================================================================
    /// \brief A subscript operator into a column
    //* =====================================================================
    [[nodiscard]] column_proxy operator[](coordinate_type column);

    //* =====================================================================
    /// \brief A subscript operator into a column
    //* =====================================================================
    [[nodiscard]] const_column_proxy operator[](coordinate_type) const;

private:
    //* =====================================================================
    /// \brief Get the value of an element.
    //* =====================================================================
    [[nodiscard]] element &get_element(
        coordinate_type column, coordinate_type row);

    //* =====================================================================
    /// \brief Get the value of an element.
    //* =====================================================================
    [[nodiscard]] element const &get_element(
        coordinate_type column, coordinate_type row) const;

    std::vector<element> grid_;
    extent size_;
};

}  // namespace terminalpp
