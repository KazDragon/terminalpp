#include "terminalpp/attribute.hpp"
#include <gtest/gtest.h>

TEST(colour_test, can_construct_from_low_colour_enum)
{
    terminalpp::ansi::graphics::colour col(
        terminalpp::ansi::graphics::colour::red);

    terminalpp::colour expected_colour = terminalpp::low_colour(col);

    auto result_colour = [](terminalpp::colour const &col)
    {
        return col;
    }(col);

    ASSERT_EQ(expected_colour, result_colour);
}
