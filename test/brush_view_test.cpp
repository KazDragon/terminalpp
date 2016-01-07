#include <terminalpp/views/brush_view.hpp>
#include <terminalpp/events/default_event_context.hpp>
#include <terminalpp/views/default_draw_context.hpp>
#include <terminalpp/models/default_brush_model.hpp>
#include <terminalpp/canvas.hpp>
#include <terminalpp/canvas_view.hpp>
#include <terminalpp/draw_context.hpp>
#include <terminalpp/event_context.hpp>
#include <terminalpp/view.hpp>
#include <gtest/gtest.h>

TEST(brush_view_test, brush_view_is_a_view)
{
    terminalpp::view view{terminalpp::views::brush_view{}};
}

TEST(brush_view_test, a_new_brush_view_has_a_preferred_size_of_zero)
{
    terminalpp::views::brush_view view;

    terminalpp::extent expected_size{0, 0};
    ASSERT_EQ(expected_size, view.get_preferred_size());
}

TEST(brush_view_test, a_new_brush_view_has_a_size_of_zero)
{
    terminalpp::views::brush_view view;

    terminalpp::extent expected_size{0, 0};
    ASSERT_EQ(expected_size, view.get_size());
}

TEST(brush_view_test, setting_the_size_changes_the_view_size)
{
    terminalpp::views::brush_view view;

    terminalpp::extent size{5, 6};
    view.set_size(size);

    ASSERT_EQ(size, view.get_size());
}

TEST(brush_view_test, setting_the_size_changes_the_preferred_size_to_the_same_value)
{
    terminalpp::views::brush_view view;

    terminalpp::extent size{5, 6};
    view.set_size(size);

    ASSERT_EQ(size, view.get_preferred_size());
}

TEST(brush_view_test, drawing_the_view_draws_the_fill_pattern)
{
    terminalpp::view view{
        terminalpp::views::brush_view{
            terminalpp::models::default_brush_model{'x'}
        }};
    view.set_size({2, 2});

    terminalpp::canvas canvas({4, 4});
    terminalpp::canvas_view canvas_view(canvas);
    canvas_view.offset_by({1, 1});

    terminalpp::draw_context dc{
        terminalpp::views::default_draw_context{canvas_view}};

    view.draw(dc, {{}, view.get_size()});

    // This should paint the following picture on the canvas:
    //
    // +----+
    // |    |
    // | XX |
    // | XX |
    // |    |
    // +----+
    ASSERT_EQ(terminalpp::element(' '), canvas[0][0]);
    ASSERT_EQ(terminalpp::element(' '), canvas[0][1]);
    ASSERT_EQ(terminalpp::element(' '), canvas[0][2]);
    ASSERT_EQ(terminalpp::element(' '), canvas[0][3]);
    ASSERT_EQ(terminalpp::element(' '), canvas[1][0]);
    ASSERT_EQ(terminalpp::element('x'), canvas[1][1]);
    ASSERT_EQ(terminalpp::element('x'), canvas[1][2]);
    ASSERT_EQ(terminalpp::element(' '), canvas[1][3]);
    ASSERT_EQ(terminalpp::element(' '), canvas[2][0]);
    ASSERT_EQ(terminalpp::element('x'), canvas[2][1]);
    ASSERT_EQ(terminalpp::element('x'), canvas[2][2]);
    ASSERT_EQ(terminalpp::element(' '), canvas[2][3]);
    ASSERT_EQ(terminalpp::element(' '), canvas[3][0]);
    ASSERT_EQ(terminalpp::element(' '), canvas[3][1]);
    ASSERT_EQ(terminalpp::element(' '), canvas[3][2]);
    ASSERT_EQ(terminalpp::element(' '), canvas[3][3]);
}

TEST(brush_view_test, events_are_unhandled)
{
    terminalpp::views::brush_view view;

    terminalpp::event_context event_context{
        terminalpp::events::default_event_context{}};

    auto const &result = view.event(event_context, {});

    ASSERT_TRUE(result.empty());
}
