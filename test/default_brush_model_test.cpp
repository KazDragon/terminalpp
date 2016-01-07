#include <terminalpp/models/default_brush_model.hpp>
#include <terminalpp/models/brush_model.hpp>
#include <gtest/gtest.h>

TEST(default_brush_model_test, default_brush_model_is_a_brush_model)
{
    terminalpp::models::brush_model model{
        terminalpp::models::default_brush_model{}};
}

TEST(default_brush_model_test, default_fill_is_unattributed_space)
{
    terminalpp::models::brush_model model{
        terminalpp::models::default_brush_model{}};

    terminalpp::element expected_fill(' ');

    ASSERT_EQ(expected_fill, model.get_fill());
}

TEST(default_brush_model_test, fill_can_be_set_in_constructor)
{
    terminalpp::element elem('x');
    elem.attribute_.foreground_colour_ = terminalpp::high_colour(5, 4, 3);

    terminalpp::models::brush_model model{
        terminalpp::models::default_brush_model{elem}};

    ASSERT_EQ(elem, model.get_fill());
}

TEST(default_brush_model_test, fill_can_be_set_from_function)
{
    terminalpp::models::default_brush_model default_model;
    terminalpp::models::brush_model model{default_model};

    terminalpp::element elem('x');
    elem.attribute_.foreground_colour_ = terminalpp::high_colour(5, 4, 3);

    default_model.set_fill(elem);

    ASSERT_EQ(elem, model.get_fill());
}
