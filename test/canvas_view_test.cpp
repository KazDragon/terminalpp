#include "terminalpp/canvas_view.hpp"
#include "terminalpp/canvas.hpp"
#include <gtest/gtest.h>

TEST(canvas_view_test, default_canvas_view_views_same_basis_as_canvas)
{
    terminalpp::canvas canvas({2, 2});
    terminalpp::canvas_view canvas_view(canvas);
    
    canvas_view[0][0] = 'a';
    canvas_view[0][1] = 'b';
    canvas_view[1][0] = 'c';
    canvas_view[1][1] = 'd';
    
    ASSERT_TRUE(canvas[0][0] == 'a');
    ASSERT_TRUE(canvas[0][1] == 'b');
    ASSERT_TRUE(canvas[1][0] == 'c');
    ASSERT_TRUE(canvas[1][1] == 'd');
}

TEST(canvas_view_test, default_canvas_view_has_same_size_as_canvas)
{
    terminalpp::canvas canvas({2, 2});
    terminalpp::canvas_view canvas_view(canvas);
    
    ASSERT_EQ(canvas.size(), canvas_view.size());
}

TEST(canvas_view_test, offset_canvas_view_has_offset_basis)
{
    terminalpp::canvas canvas({2, 2});
    terminalpp::canvas_view canvas_view(canvas);
    
    canvas_view.offset_by({1, 1});
    canvas_view[0][0] = 'x';
    ASSERT_TRUE(canvas_view[0][0] == 'x');
    
    ASSERT_TRUE(canvas[0][0] == ' ');
    ASSERT_TRUE(canvas[0][1] == ' ');
    ASSERT_TRUE(canvas[1][0] == ' ');
    ASSERT_TRUE(canvas[1][1] == 'x');
}

TEST(canvas_view_test, offset_canvas_view_has_reduced_size)
{
    terminalpp::canvas canvas({2, 2});
    terminalpp::canvas_view canvas_view(canvas);
    
    canvas_view.offset_by({1, 1});
    
    ASSERT_EQ(
        (canvas.size() - terminalpp::extent{1, 1}),
        canvas_view.size());
}

TEST(canvas_view_test, offset_is_cumulative)
{
    terminalpp::canvas canvas({3, 3});
    terminalpp::canvas_view canvas_view(canvas);
    
    canvas_view.offset_by({1, 1});
    canvas_view.offset_by({1, 1});
    
    canvas_view[0][0] = 'x';
    ASSERT_TRUE(canvas[2][2] == 'x');
}
