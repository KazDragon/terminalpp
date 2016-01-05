#include <terminalpp/views/default_view_context.hpp>
#include <terminalpp/view_context.hpp>
#include <terminalpp/canvas.hpp>
#include <terminalpp/canvas_view.hpp>
#include <gtest/gtest.h>

TEST(default_view_context_test, default_view_context_is_a_view_context)
{
    terminalpp::canvas canvas{{}};
    terminalpp::canvas_view canvas_view(canvas);

    terminalpp::view_context vc{
        terminalpp::views::default_view_context{canvas_view}};
}