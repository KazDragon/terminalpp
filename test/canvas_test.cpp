#include "terminalpp/canvas.hpp"

#include <gtest/gtest.h>

TEST(canvas_test, can_perform_loops_over_a_canvas)
{
    terminalpp::canvas canvas({5, 5});
    auto size = canvas.size();

    ASSERT_EQ(terminalpp::extent(5, 5), size);

    for (auto &&elem : canvas)
    {
        elem = {'x'};
    }

    for (terminalpp::coordinate_type row = 0; row < size.height_; ++row)
    {
        for (terminalpp::coordinate_type column = 0; column < size.width_;
             column++)
        {
            auto expected = terminalpp::element('x');
            auto result = terminalpp::element(canvas[column][row]);
            ASSERT_EQ(expected, result);
        }
    }
}

TEST(canvas_test, can_perform_loops_over_a_const_canvas)
{
    terminalpp::canvas canvas({5, 5});
    auto size = canvas.size();

    ASSERT_EQ(terminalpp::extent(5, 5), size);

    for (auto &&elem : canvas)
    {
        elem = {'x'};
    }

    terminalpp::canvas const &ccanvas = canvas;

    for (terminalpp::coordinate_type row = 0; row < size.height_; ++row)
    {
        for (terminalpp::coordinate_type column = 0; column < size.width_;
             column++)
        {
            auto expected = terminalpp::element('x');
            auto result = terminalpp::element(ccanvas[column][row]);
            ASSERT_EQ(expected, result);
        }
    }
}

TEST(canvas_test, can_assign_from_canvas_to_canvas)
{
    terminalpp::canvas canvas_source({1, 1});
    terminalpp::canvas canvas_dest({1, 1});

    canvas_dest[0][0] = canvas_source[0][0];
}

TEST(canvas_test, resizing_canvas_larger_keeps_content)
{
    auto small_size = terminalpp::extent{5, 6};
    auto large_size = terminalpp::extent{10, 9};

    terminalpp::canvas canvas(small_size);

    for (auto &&elem : canvas)
    {
        elem = {'x'};
    }

    canvas.resize(large_size);
    ASSERT_EQ(large_size, canvas.size());

    for (terminalpp::coordinate_type row = 0; row < large_size.height_; ++row)
    {
        for (terminalpp::coordinate_type column = 0; column < large_size.width_;
             ++column)
        {
            auto expected =
                row < small_size.height_ && column < small_size.width_
                    ? terminalpp::element{'x'}
                    : terminalpp::element{' '};

            auto result = terminalpp::element(canvas[column][row]);
            ASSERT_EQ(expected, result);
        }
    }
}

TEST(canvas_test, resizing_canvas_smaller_truncates_content)
{
    auto small_size = terminalpp::extent{5, 6};
    auto large_size = terminalpp::extent{10, 9};

    terminalpp::canvas canvas(large_size);

    for (terminalpp::coordinate_type row = 0; row < large_size.height_; ++row)
    {
        for (terminalpp::coordinate_type column = 0; column < large_size.width_;
             ++column)
        {
            canvas[column][row] = {static_cast<terminalpp::byte>(column * row)};
        }
    }

    canvas.resize(small_size);

    for (terminalpp::coordinate_type row = 0; row < small_size.height_; ++row)
    {
        for (terminalpp::coordinate_type column = 0; column < small_size.width_;
             ++column)
        {
            auto expected = terminalpp::element(
                static_cast<terminalpp::byte>(column * row));
            auto result = terminalpp::element(canvas[column][row]);

            ASSERT_EQ(expected, result);
        }
    }
}
