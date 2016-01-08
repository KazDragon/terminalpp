#include "terminalpp/rectangle.hpp"
#include <gtest/gtest.h>

TEST(rectangle_test, default_constructed_rectangle_is_at_origin_with_no_size)
{
    terminalpp::rectangle rect;
    terminalpp::point expected_origin{0, 0};
    terminalpp::extent expected_size{0, 0};

    ASSERT_EQ(expected_origin, rect.origin);
    ASSERT_EQ(expected_size, rect.size);
}

TEST(rectangle_test, can_be_constructed_from_origin_and_size)
{
    terminalpp::point origin{1, 2};
    terminalpp::extent size{3, 4};

    terminalpp::rectangle rect(origin, size);

    ASSERT_EQ(origin, rect.origin);
    ASSERT_EQ(size, rect.size);
}

TEST(rectangle_test, adding_an_extent_to_a_point_yields_a_rectangle)
{
    terminalpp::point origin{1, 2};
    terminalpp::extent size{3, 4};

    terminalpp::rectangle rect = origin + size;

    ASSERT_EQ(origin, rect.origin);
    ASSERT_EQ(size, rect.size);
}

TEST(rectangle_test, rectangles_compare_equal_to_similar_rectangles)
{
    terminalpp::rectangle rect_lhs{{1, 2}, {3, 4}};
    terminalpp::rectangle rect_rhs{{1, 2}, {3, 4}};

    ASSERT_TRUE(rect_lhs == rect_rhs);
}

TEST(rectangle_test, rectangles_do_not_compare_equal_to_dissimilar_rectangles)
{
    terminalpp::rectangle rect_lhs{{1, 2}, {3, 4}};
    terminalpp::rectangle rect_with_different_origin{{2, 3}, {3, 4}};
    terminalpp::rectangle rect_with_different_size{{1, 2}, {4, 5}};
    terminalpp::rectangle rect_different{{5, 6}, {7, 8}};

    ASSERT_FALSE(rect_lhs == rect_with_different_origin);
    ASSERT_FALSE(rect_lhs == rect_with_different_size);
    ASSERT_FALSE(rect_lhs == rect_different);
}

TEST(rectangle_test, rectangles_do_not_compare_unequal_to_similar_rectangles)
{
    terminalpp::rectangle rect_lhs{{1, 2}, {3, 4}};
    terminalpp::rectangle rect_rhs{{1, 2}, {3, 4}};

    ASSERT_FALSE(rect_lhs != rect_rhs);
}

TEST(rectangle_test, rectangles_compare_unequal_to_dissimilar_rectangles)
{
    terminalpp::rectangle rect_lhs{{1, 2}, {3, 4}};
    terminalpp::rectangle rect_with_different_origin{{2, 3}, {3, 4}};
    terminalpp::rectangle rect_with_different_size{{1, 2}, {4, 5}};
    terminalpp::rectangle rect_different{{5, 6}, {7, 8}};

    ASSERT_TRUE(rect_lhs != rect_with_different_origin);
    ASSERT_TRUE(rect_lhs != rect_with_different_size);
    ASSERT_TRUE(rect_lhs != rect_different);
}